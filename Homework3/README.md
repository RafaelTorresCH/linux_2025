# Assignment Sensor Service

## Clone & Build
### Prerequisites
- `gcc`
- `make`
- `systemd`

### Commands
```bash
# Clone the repository
git clone https://github.com/RafaelTorresCH/linux_2025.git
cd linux_2025/Homework3

# Build the project
make
```

## Install & Enable
1. Copy the binary to `/usr/local/bin`:
   ```bash
   sudo cp assignment-sensor /usr/local/bin/
   ```
2. Copy the systemd service file to `/etc/systemd/system`:
   ```bash
   sudo cp systemd/assignment-sensor.service /etc/systemd/system/
   ```
3. Reload systemd to recognize the new service:
   ```bash
   sudo systemctl daemon-reload
   ```
4. Enable and start the service:
   ```bash
   sudo systemctl enable --now assignment-sensor
   ```

## Configuration
The service supports the following CLI flags:
- `--interval`: Interval in seconds between sensor readings (default: 5 seconds).
- `--logfile`: Path to the log file (default: `/tmp/assignment_sensor.log`).
- `--device`: Path to the device file (default: `/dev/urandom`).

## Testing
1. Check the service status:
   ```bash
   sudo systemctl status assignment-sensor
   ```
2. View the log file:
   ```bash
   cat /tmp/assignment_sensor.log
   ```
3. Test SIGTERM handling:
   ```bash
   sudo systemctl stop assignment-sensor
   ```
4. Simulate `/tmp` being unwritable:
   ```bash
   sudo chmod 000 /tmp
   sudo systemctl restart assignment-sensor
   # Logs will now be written to /var/tmp/assignment_sensor.log
   sudo chmod 1777 /tmp # Restore permissions
   ```

## Uninstall
1. Disable the service:
   ```bash
   sudo systemctl disable --now assignment-sensor
   ```
2. Remove the binary and service file:
   ```bash
   sudo rm /usr/local/bin/assignment-sensor
   sudo rm /etc/systemd/system/assignment-sensor.service
   ```
3. Reload systemd:
   ```bash
   sudo systemctl daemon-reload
   ```

## Fallback Behavior
If `/tmp` is not writable, the service will automatically fall back to logging in `/var/tmp/assignment_sensor.log`.

## Why `/dev/urandom`?
`/dev/urandom` was chosen as a mock sensor because it provides a stream of random data, simulating sensor readings in a simple and reliable way.

## Notes
- The service runs as `root` by default. To change this, edit the `assignment-sensor.service` file and add a `User=` line under the `[Service]` section.
  ```
  User=your-username
  ```
