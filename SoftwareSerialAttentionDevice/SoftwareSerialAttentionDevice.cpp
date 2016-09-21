#include "SoftwareSerialAttentionDevice.h"
#include <Arduino.h>

SoftwareSerialAttentionDevice::SoftwareSerialAttentionDevice(unsigned char receivePin, unsigned char transmitPin)
        : SoftwareSerial(receivePin, transmitPin), rxBufferPos(0), responseFullyRead(true) {
    rxBuffer[0] = '\0';
}

bool SoftwareSerialAttentionDevice::sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout) {
    if (sendCommand(command, append, timeout) == 0) {
        return false;
    }
    return doesResponseContains(expectation);
}

bool SoftwareSerialAttentionDevice::doesResponseContains(const char *expectation) {
    return findInResponse(expectation) != NULL;
}

unsigned int SoftwareSerialAttentionDevice::sendCommand(const char *command, bool append, unsigned long timeout) {
    rxBufferPos = 0;
    rxBuffer[0] = '\0';
    flush();
    if (append) {
        print("AT");
    }
    println(command);
    return readResponse(timeout);
}

unsigned int SoftwareSerialAttentionDevice::readResponse(unsigned long timeout, bool append) {
    int availableBytes;
    unsigned long pos, last, now, start;
    unsigned int read;
    last = start = millis();
    if (!append) {
        rxBufferPos = 0;
    }
    pos = rxBufferPos;
    responseFullyRead = true;
    while (available() <= 0 && (millis() - start) < timeout)
        ;
    start = millis();
    do {
        availableBytes = available();
        if (availableBytes > 0) {
            if (rxBufferPos + availableBytes >= AT_DEVICE_RX_BUFFER_SIZE) {
                availableBytes = AT_DEVICE_RX_BUFFER_SIZE - (rxBufferPos + 1);
                responseFullyRead = false;
            }
            if (availableBytes > 0) {
                last = millis();
                // we have the guaranty that is not going to be too big because it is constrained by the buffer size.
                read = readBytes((char *) &rxBuffer[rxBufferPos], availableBytes);
                rxBufferPos += read;
                rxBuffer[rxBufferPos] = '\0';
            }
        }
        now = millis();
    } while ((availableBytes > 0 || (now - last) < AT_DEVICE_SERIAL_INTERBYTE_TIMEOUT) && (now - start) < timeout && responseFullyRead);
    return rxBufferPos - pos;
}

bool SoftwareSerialAttentionDevice::wasResponseFullyRead() {
    return responseFullyRead;
}

const char *SoftwareSerialAttentionDevice::findInResponse(const char *str) {
    return strstr((const char *) &rxBuffer[0], str);
}

int SoftwareSerialAttentionDevice::waitUntilReceive(const char *str, unsigned int timeout) {
    const char *pos;
    while ((pos = findInResponse(str)) == NULL && readResponse(timeout, responseFullyRead) > 0)
        ;
    if (pos != NULL) {
        return (int) (pos - (const char *) &rxBuffer[0]);
    }
    return -1;
}

void SoftwareSerialAttentionDevice::discardBuffer() {
    rxBuffer[0] = '\0';
}
