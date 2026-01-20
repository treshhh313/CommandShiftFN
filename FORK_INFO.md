# CommandShift Fork - Fn Screenshot Shortcuts

This fork adds Fn key screenshot shortcuts to the original CommandShift application.

## What's Different From Original?

### New Feature: Fn Screenshot Shortcuts
- **Short press Fn** (< 500ms): Triggers `Command+Shift+4` for area screenshot
- **Long press Fn** (≥ 500ms): Triggers `Command+Shift+5` for screenshot control panel
- Toggle on/off via menu: "Enable Fn screenshot shortcuts"
- Settings persist across restarts

### Removed
- "Shift + Fn" option for language switching (Fn key is now dedicated to screenshots when feature is enabled)

## Building

This fork includes automated builds via GitHub Actions. DMG files are automatically built and released when you push a tag.

### Manual Build
```bash
brew install qt@5
cd src
qmake CommandShift.pro
make
```

## Releasing a New Version

1. Update version number if needed
2. Commit your changes
3. Create and push a tag:
   ```bash
   git tag v1.0.0-fn
   git push origin v1.0.0-fn
   ```
4. GitHub Actions will automatically build the DMG and create a release

## Credits

Original CommandShift by [Vasyl Baran](https://github.com/VasylBaran/CommandShift)

Fn screenshot feature fork by [treshhh313](https://github.com/treshhh313)
