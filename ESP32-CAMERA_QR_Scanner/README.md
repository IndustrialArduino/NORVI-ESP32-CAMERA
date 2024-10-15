# QR Code Scanner using ESP32 Camera

This project demonstrates how to scan and decode QR codes using an ESP32 Camers. The code captures QR codes continuously and prints the decoded payload to the serial monitor.

## Features

- Real-time QR code scanning using the ESP32 camera.
- Serial output of the QR code payload.
- Runs the QR code task on Core 1 for non-blocking performance.
- Detects invalid QR codes and reports them via serial output.

## Code Overview

### 1.QR Code Task (onQrCodeTask)

- Continuously scans for QR codes and decodes them.
- Prints valid QR code payloads to the serial monitor.
- If an invalid code is detected, an error message is displayed.

### 2.Task Execution on Core 1

-Runs the QR code scanning task on Core 1 for smooth multitasking.

## Serial Output Example

```bash
Setup QRCode Reader  
Begin on Core 1  
Found QRCode  
Payload: https://norvi.lk  
Found QRCode  
Invalid: ERROR_CODE
```
