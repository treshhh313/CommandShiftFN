# Quick Start Guide for GitHub Fork Setup

## ✅ What's Been Set Up

1. **Updated README.md** - Describes your fork and the new Fn screenshot feature
2. **GitHub Actions Workflows**:
   - `ci.yml` - Builds on every push to main
   - `build-release.yml` - Creates DMG releases when you push a tag
3. **Documentation**:
   - `FORK_INFO.md` - Fork-specific details
   - `RELEASE.md` - How to create releases

## 🚀 Next Steps

### 1. Commit and Push These Files

```bash
git commit -m "Add GitHub Actions for automated DMG builds and update README"
git push origin main
```

### 2. Create Your First Release

```bash
# Create a tag for version 1.0.0-fn
git tag -a v1.0.0-fn -m "First fork release with Fn screenshot shortcuts"

# Push the tag to trigger the build
git push origin v1.0.0-fn
```

### 3. Monitor the Build

1. Go to your GitHub repo: https://github.com/treshhh313/CommandShiftFN
2. Click on the "Actions" tab
3. Watch the "Build and Release DMG" workflow run
4. When complete, check the "Releases" page for your DMG!

## 📦 What the Build Process Does

1. **Installs Qt 5** on GitHub's macOS runner
2. **Compiles** your fork using qmake
3. **Creates DMG** with the app and Applications symlink
4. **Calculates MD5** checksum for verification
5. **Creates GitHub Release** with:
   - DMG file
   - Checksum file
   - Release notes describing the new feature

## 🔧 Customizing the Build

Edit `.github/workflows/build-release.yml` to:
- Change Qt version
- Modify DMG appearance
- Update release notes template
- Add code signing (requires Apple Developer account)

## ℹ️ Important Notes

- Builds only trigger on **tags starting with 'v'** (e.g., v1.0.0-fn, v1.1.0-fn)
- CI builds run on every push to main (no release created)
- The `-fn` suffix in version tags indicates "fork" version
- DMG files are universal binaries (Intel + Apple Silicon)

## 🐛 Troubleshooting

**Build fails?**
- Check Actions logs for error messages
- Ensure Qt can build the project locally first
- Verify all source files are committed

**No release created?**
- Make sure you pushed a tag (not just committed)
- Tag must start with 'v'
- Check Actions tab for workflow status

---

**Ready to go!** Just commit, push, and create your first tag! 🎉
