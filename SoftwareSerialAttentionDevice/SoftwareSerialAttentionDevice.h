/**
 * Arduino - AT device
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SOFTWARE_SERIAL_ATTENTION_DEVICE_H__
#define __ARDUINO_SOFTWARE_SERIAL_ATTENTION_DEVICE_H__ 1

#include <SoftwareSerial.h>
#include <AttentionDevice.h>

#define AT_DEVICE_RX_BUFFER_SIZE                    256
#define AT_DEVICE_DEFAULT_COMMAND_RESPONSE_TIMEOUT  1000UL
#define AT_DEVICE_SERIAL_INTERBYTE_TIMEOUT          50UL

class SoftwareSerialAttentionDevice : public SoftwareSerial, public AttentionDevice {

    /**
     * RX buffer.
     */
    unsigned char rxBuffer[AT_DEVICE_RX_BUFFER_SIZE];

    /**
     * RX buffer position.
     */
    unsigned int rxBufferPos;

    /**
     * Bool indicating the last command's response was fully read by
     * readResponse method.
     */
    bool responseFullyRead;

public:

    SoftwareSerialAttentionDevice(unsigned char receivePin, unsigned char transmitPin);

    /**
     * Get a pointer to the last response.
     *
     * @return
     */
    unsigned char *getLastResponse() {
        return &rxBuffer[0];
    }

    /**
     * Sends a command expecting some result.
     *
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @param timeout           The maximum time to perform the op.
     * @return
     */
    bool sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout);

    /**
     * Sends a command expecting some result.
     *
     * @param   command             The command string, should be \0 ended.
     * @param   expectation         The expectation string.
     * @param   append              If should append AT+ in the command.
     * @return
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation, bool append) {
        return sendCommandExpecting(command, expectation, append, AT_DEVICE_DEFAULT_COMMAND_RESPONSE_TIMEOUT);
    }

    /**
     * Sends a command expecting some result.
     *
     * @param   command             The command string, should be \0 ended.
     * @param   expectation         The expectation string.
     * @param   timeout             Timeout.
     * @return
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation, unsigned long timeout) {
        return sendCommandExpecting(command, expectation, false, timeout);
    }

    /**
     * Sends a command expecting some result.
     *
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @return
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation) {
        return sendCommandExpecting(command, expectation, (bool) false);
    }

    /**
     * Checks if the last response contains the given sub-string.
     *
     * @param expectation       The expectation string.
     * @return
     */
    bool doesResponseContains(const char *expectation);

    /**
     * Sends a command to the device.
     *
     * @param command           The command string, should be \0 ended.
     * @param timeout           The maximum time to perform the op.
     * @return
     */
    unsigned int sendCommand(const char *command, bool append, unsigned long timeout);

    /**
     * Sends a command to the device.
     *
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return
     */
    inline unsigned int sendCommand(const char *command, bool append) {
        return sendCommand(command, append, 1000);
    }

    /**
     * Sends a command to the device.
     *
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return
     */
    inline unsigned int sendCommand(const char *command, unsigned long timeout) {
        return sendCommand(command, (bool) false, timeout);
    }

    /**
     * Sends a command to the device.
     *
     * @param command           The command string, should be \0 ended.
     * @return
     */
    inline unsigned int sendCommand(const char *command) {
        return sendCommand(command, (bool) false);
    }

    /**
     * Sends a command to the device.
     */
    inline unsigned int sendCommand() {
        return sendCommand("");
    }

    /**
     * Reads the response from the device.
     *
     * @param timeout           The maximum time to perform the op.
     * @return                  How many bytes was received. 0 if timeout.
     */
    inline unsigned int readResponse(unsigned long timeout) {
        return readResponse(timeout, false);
    }

    /**
     * Reads the response from the device.
     *
     * @param timeout           The maximum time to perform the op.
     * @param append            Append the response in the internal buffer.
     * @return                  How many bytes was received. 0 if timeout.
     */
    unsigned int readResponse(unsigned long timeout, bool append);

    /**
     * Checks if the rx is fully read.
     *
     * If false, a new call to readResponse will read more data from tx
     * placing the new data over the current data in it. Consecutive calls to
     * readResponse will write data into the same buffer.
     *
     * use getLastResponse to consume the current data and then call readResponse again
     * in case tx was not fully read.
     */
    bool wasResponseFullyRead();

    /**
     * Searches the response for a given string.
     *
     * @param   str     The string to be searched inside response
     * @return          The pointer to the first found string, NULL if not found
     */
    const char *findInResponse(const char *str);

    /**
     * Keeps reading the response until finds the str or timeout.
     *
     * @param   str         String it tries to find
     * @param   timeout     Timeout in millis
     * @return              The position to the first char it finds in the internal buffer, -1 otherwise
     */
    int waitUntilReceive(const char *str, unsigned int timeout);

    /**
     * Discards the internal buffer.
     */
    void discardBuffer();
};

#endif /* __ARDUINO_SOFTWARE_SERIAL_ATTENTION_DEVICE_H__ */
