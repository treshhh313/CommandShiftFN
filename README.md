
# CommandShift Fork with Fn Screenshot Shortcuts

> [!NOTE]
> This is a fork of [VasylBaran/CommandShift](https://github.com/VasylBaran/CommandShift) with additional **Fn key screenshot shortcuts** feature.

## 🆕 New Feature: Fn Screenshot Shortcuts

This fork adds a new feature that allows the **Fn key** to trigger macOS screenshot shortcuts:

- **Short press** (< 500ms): `Command + Shift + 4` → Area screenshot tool
- **Long press** (≥ 500ms): `Command + Shift + 5` → Screenshot control panel

### How to Use
1. Install and launch CommandShift
2. Click the menu bar icon (CS)
3. Check **"Enable Fn screenshot shortcuts"**
4. Now you can use Fn key for quick screenshots!

### Why This Feature?
Makes taking screenshots much faster and more convenient - no need to remember complex keyboard combinations or reach for multiple keys simultaneously.

---

## Original CommandShift Features

CommandShift is a free and open-source app that allows you to change input source using Windows-style shortcuts (e.g. Command + Shift, Option + Shift, Control + Shift, or even just Shift). 

By default MacOS doesn't support shortcuts that consist of modifier keys only. CommandShift solves this problem.

## How-to Install

### Download Pre-built DMG
Check the [Releases](https://github.com/treshhh313/CommandShiftFN/releases) page for the latest build.

### Build from Source
```bash
# Prerequisites: Qt 5 or Qt 6, qmake, Xcode Command Line Tools
git clone https://github.com/treshhh313/CommandShiftFN.git
cd CommandShiftFN/src
qmake CommandShift.pro
make
```

### Installation Steps
1. Download CommandShift-universal.dmg
2. Drag'n'drop CommandShift application from dmg-file to your Applications folder
3. Add CommandShift to **"System Settings → Privacy & Security → Accessibility"** for it to work properly
4. Enjoy!
5. (Optional) Add CommandShift to your startup items ("System Settings → General → Login Items")

## Features

✅ **Language Switching:**
- Switch languages with Windows-style shortcuts
- Choose from: Shift + Control, Shift + Option, Shift + Command, or just Shift
- Option to switch language on key press or release

✅ **Fn Screenshot Shortcuts (New!):**
- Quick tap Fn → Area screenshot (Command+Shift+4)
- Hold Fn → Screenshot menu (Command+Shift+5)
- Toggle on/off via menu

✅ **Customization:**
- Hide tray icon permanently or temporarily
- White icon option for better visibility
- Settings persist across restarts

✅ **Universal Binary:**
- Runs natively on both Intel and Apple Silicon Macs

## FAQ

### Fn Screenshot Feature

* **Q:** I get "App is damaged and can't be opened" error
* **A:** This is normal for unsigned apps. Run this in Terminal:
  ```bash
  sudo xattr -cr /path/to/CommandShift.app
  ```

* **Q:** Fn key is not triggering screenshots
* **A:** Make sure the feature is enabled in the menu AND CommandShift has Accessibility permissions in System Settings

* **Q:** Can I adjust the timing threshold?
* **A:** Currently it's 500ms (hardcoded). You can modify it in the source code and rebuild.

### Original FAQ

* **Q:** How do I choose which shortcut should switch language?
* **A:** Find CommandShift icon in menu bar and click it, there you'll find "Change language with..." drop-down

* **Q:** I get "CommandShift is damaged and can't be opened" error
* **A:** Run this command in Terminal: `xattr -cr /Applications/CommandShift.app`

* **Q:** I want to switch language after releasing Shift key instead of when pressing it
* **A:** Toggle 'Change language after Shift release' from the menu

* **Q:** I want to hide CommandShift icon from menu tray
* **A:** Select "Tray menu icon..." → choose "Hide icon permanently" or "Hide icon until restart"

* **Q:** I use 3+ languages and CommandShift switches only between the last 2
* **A:** Press and hold the second key, then press Shift multiple times to cycle through all languages

## Downloads

### This Fork
* [Releases](https://github.com/treshhh313/CommandShiftFN/releases) - Latest builds with Fn screenshot feature

### Original CommandShift
* Sourceforge: https://sourceforge.net/projects/commandshift/files/
* GitHub: https://github.com/VasylBaran/CommandShift/releases/

## Credits

This is a fork of the amazing **CommandShift** by [Vasyl Baran](https://github.com/VasylBaran).

**Original Author:** Vasyl Baran (Ukrainian software engineer)

If you find CommandShift useful, please consider supporting the original author:
* **Buy Me a Coffee:** https://buymeacoffee.com/vasylbaran
* **Patreon:** https://www.patreon.com/Vasyl_Baran

The original author's goal is $99 for Apple Developer program membership to properly sign and notarize CommandShift.

## License

Same license as the original CommandShift project (see [LICENSE](LICENSE)).

---

🇺🇦 **Stand with Ukraine!** Stay Safe and stay Strong!
