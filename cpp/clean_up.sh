#!/bin/bash
# Clean up C++ build artifacts
rm -f *.o *.out *.exe a.out
rm -f **/a.out **/*.o **/*.out **/*.exe
rm -f **/*/a.out **/*/*.o **/*/*.out **/*/*.exe

# Clean up executable files without extension
find . -type f -executable -not -name "*.*" -not -name "clean_up.sh" -exec rm -f {} \;
# Clean up dSYM folders (debug symbol files created by macOS compilers)
find . -type d -name "*.dSYM" -exec rm -rf {} \; 2>/dev/null || true
echo "Cleanup complete!"