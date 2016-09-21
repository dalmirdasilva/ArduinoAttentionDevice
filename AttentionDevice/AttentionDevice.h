/**
 * Arduino - AT device
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_ATTENTION_DEVICE_H__
#define __ARDUINO_ATTENTION_DEVICE_H__ 1

class AttentionDevice {

public:

    /**
     * Sends a command expecting some result.
     *
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @param timeout           The maximum time to perform the op.
     * @return
     */
    virtual bool sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout) = 0;

    /**
     * Checks if the last response contains the given sub-string.
     *
     * @param expectation       The expectation string.
     * @return
     */
    virtual bool doesResponseContains(const char *expectation) = 0;

    /**
     * Sends a command to the device.
     *
     * @param command           The command string, should be \0 ended.
     * @param timeout           The maximum time to perform the op.
     * @return
     */
    virtual unsigned int sendCommand(const char *command, bool append, unsigned long timeout) = 0;

    /**
     * Reads the response from the device.
     *
     * @param timeout           The maximum time to perform the op.
     * @param append            Append the response in the internal buffer.
     * @return                  How many bytes was received. 0 if timeout.
     */
    virtual unsigned int readResponse(unsigned long timeout, bool append) = 0;

    /**
     * Keeps reading the response until finds the str or timeout.
     *
     * @param   str         String it tries to find
     * @param   timeout     Timeout in millis
     * @return              The position to the first char it finds in the internal buffer, -1 otherwise
     */
    virtual int waitUntilReceive(const char *str, unsigned int timeout) = 0;
};

#endif /* __ARDUINO_ATTENTION_DEVICE_H__ */
