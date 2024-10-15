# ESP32-Camera QR code scanner with display

This project demonstrates QR code scanning using an NORVI-ESP32 camera. The code captures QR codes through the camera and displays the decoded payload on camera screen.

## Features

- Captures and decodes QR codes using the camera and display the payload on camera display.
- Filters out repeated QR codes within 10 seconds to avoid redundancy.
- Processes QR code tasks on Core 1 for smooth operation.

## Code Overview

### 1.QR Code Task (onQrCodeTask)

- Continuously scans for QR codes.
- If a valid code is detected, the payload is printed on the display.
- Prevents duplicate processing by storing the last scanned payload.
- Resets the payload after 10 seconds of inactivity.

### 2.Camera Setup

- Uses ESP32QRCodeReader to initialize camera and handle decoding.
- Autofocus is enabled for better code recognition.

## Serial Output Example

```bash
OV5640_Focus_Init Successful!  
OV5640_Auto_Focus Successful!
Setup QRCode Reader  
Begin on Core 1  
Found QRCode  
Payload: https://norvi.lk  
Last payload reset due to inactivity

```
