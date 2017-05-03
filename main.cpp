#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <iostream>
#include <canframeid.h>

using namespace std;

// Global.
QObject *object;
QCanBusDevice *device;

int decodeFrame(const QCanBusFrame &frame)
{
    int value;
    const QByteArray payload = frame.payload();

    if(frame.isValid())
    {
        switch(frame.frameId())
        {
            case E46_ENGINE_RPM:
            {
                unsigned short b3, b4;

                b3 = payload[2];
                b4 = payload[3];

                value = ((b4 * 256) + b3) / 6.4;
                break;
            }
            /*case VEHICLE_SPEED:
                break;*/
            case E46_FUEL_LEVEL:
            {
                const float fuelCapacity = 62.83784;
                unsigned short b2;

                b2 = payload[1];

                value = ((b2 / fuelCapacity) / 2) * 100;
                break;
            }
            case E46_COOLANT_TEMP:
            {
                unsigned short b2;

                b2 = payload[1];

                value = (b2 * 0.75) - 48.373;
                break;
            }
            case E46_OIL_TEMP:
            {
                unsigned short b5;

                b5 = payload[4];

                value = b5 - 48.373;
                break;
            }
        }

        return value;
    }

    value = 1;

    return value;
}

void checkFrames()
{
    // Read frames.
    while(device->framesAvailable() > 0)
    {
        object->setProperty("filtering", "Yes");
        object->setProperty("frames", device->framesAvailable());

        QCanBusFrame frame = device->readFrame();

        object->setProperty("canId", frame.frameId());
        object->setProperty("payload", frame.payload().data());

        if(frame.isValid())
        {
            switch(frame.frameId())
            {
                case E46_ENGINE_RPM:
                    object->setProperty("rpm", decodeFrame(frame));
                    break;
                /*case VEHICLE_SPEED:
                    object->setProperty("speed", decodeFrame(frame));
                    break;*/
                case E46_FUEL_LEVEL:
                    object->setProperty("fuel", decodeFrame(frame));
                    break;
                case E46_COOLANT_TEMP:
                    object->setProperty("coolant", decodeFrame(frame));
                    break;
                case E46_OIL_TEMP:
                    object->setProperty("oil", decodeFrame(frame));
                    break;
                default:
                    break;
            }
        }
    }
}

QCanBusDevice::Filter setCanFilter(const unsigned short &id)
{
    QCanBusDevice::Filter filter;

    filter.frameId = id;
    filter.frameIdMask = 0x7FFu; // Compare against all 11-bits of frame id.
    filter.format = QCanBusDevice::Filter::MatchBaseFormat;
    filter.type = QCanBusFrame::DataFrame;

    return filter;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Load gauge UI.
    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    object = component.create();


/************************************** CAN Bus functionality ***************************************/

    if(QCanBus::instance()->plugins().contains("socketcan"))
    {
        object->setProperty("socket", "Yes");

        // Create CAN bus device and connect to can0 via SocketCAN plugin.
        device = QCanBus::instance()->createDevice("socketcan", "can0");

        device->connectDevice();

        // Apply filters to CAN Bus device.
        QList<QCanBusDevice::Filter> filterList;

        filterList.append(setCanFilter(E46_ENGINE_RPM));
        //filterList.append(setCanFilter(E46_VEHICLE_SPEED));
        filterList.append(setCanFilter(E46_FUEL_LEVEL));
        filterList.append(setCanFilter(E46_COOLANT_TEMP));
        filterList.append(setCanFilter(E46_OIL_TEMP));

        device->setConfigurationParameter(QCanBusDevice::RawFilterKey, QVariant::fromValue(filterList));

        // Connect framesRecieved signal to slot function for reading frames.
        QObject::connect(device, &QCanBusDevice::framesReceived, checkFrames);

        if(device->state() == QCanBusDevice::ConnectedState)
        {
            object->setProperty("status", "Connected");
        }
    }

    object->setProperty("ended", "Yes");

    return app.exec();
}
