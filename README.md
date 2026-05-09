# IceWM Control Panel Plus

A modern, modular control panel for IceWM window manager with enhanced customization and system monitoring.

## Features
- Modular tab-based interface
- Customizable appearance and behavior
- System monitoring widgets
- Application launchers and shortcuts
- Multi-panel support
- Extensible plugin architecture

## Prerequisites
- IceWM 1.2.0 or later
- C++17 compiler
- CMake 3.15 or later
- gtkmm 3.24 or later (for GUI components)

## Installation
### From Source
```bash
git clone https://github.com/BaptistMissionsOS/icewm-control-panel-plus.git
cd icewm-control-panel-plus
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
sudo make install
```

### From Package (Debian/Ubuntu)
```bash
sudo apt install icewm-control-panel-plus
```

## Usage
Launch the control panel from your application menu or run:
```bash
icewm-control-panel-plus
```

## Configuration
The panel can be customized through the Preferences tab:
- Change themes and colors
- Add or remove panels
- Configure system monitoring
- Set keyboard shortcuts

## Building and Development
```bash
# Run tests
ctest

# Generate documentation
doxygen Doxyfile
```

## Contributing
Contributions are welcome! Please read our [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License
Distributed under the GPL3 License. See `LICENSE` for more information.

## Contact
- Maintainer: Your Name (baptistmissionsos@gmail.com)
- Issue Tracker: https://github.com/BaptistMissionsOS/icewm-control-panel-plus/issues

**Warning:** Do **not** run this early build as your regular user. Create a dedicated `icewm` user for testing.
