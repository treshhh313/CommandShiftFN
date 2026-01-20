# Release Instructions

## How to Create a New Release

1. **Make sure all changes are committed**
   ```bash
   git status
   ```

2. **Create a version tag**
   ```bash
   # Format: v{major}.{minor}.{patch}-fn
   # Example for first fork release:
   git tag -a v1.0.0-fn -m "First release with Fn screenshot shortcuts"
   ```

3. **Push the tag to GitHub**
   ```bash
   git push origin v1.0.0-fn
   ```

4. **GitHub Actions will automatically:**
   - Build the app on macOS
   - Create a DMG file
   - Calculate MD5 checksum
   - Create a GitHub Release with the DMG attached

5. **Check the Actions tab** on GitHub to monitor the build progress

## Version Numbering

Use the format: `v{major}.{minor}.{patch}-fn`

- The `-fn` suffix indicates this is the fork version
- Example: `v1.0.0-fn`, `v1.0.1-fn`, `v1.1.0-fn`

## Manual Build (Optional)

If you want to build locally before releasing:

```bash
# Install Qt if needed
brew install qt@5

# Build
cd src
qmake CommandShift.pro
make

# The app will be in src/CommandShift.app
```

## Testing Before Release

1. Build locally
2. Test the Fn screenshot feature
3. Test language switching still works
4. Verify settings persistence
5. Only then create the release tag

## Troubleshooting

- **Build fails on GitHub**: Check the Actions logs for errors
- **DMG not created**: Ensure the build succeeded first
- **Release not created**: Make sure you pushed a tag starting with `v`
