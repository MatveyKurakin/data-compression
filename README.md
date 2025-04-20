# Data compression 
A file archiver based on the Huffman compression algorithm.
## How to build
1. Clone the repository:
```bash
git clone https://github.com/ваш-логин/huffman-archiver.git
```
2. Go to the catalog:
```bash
cd data-compression
```
3. Create a build directory and navigate to it:
```bash
mkdir build && cd build
```
4. Build the project:
```bash
cmake ..
```
5. Build the project in the Release mode:
```bash
cmake --build . --config Release
```
## How to use
1. File compression
```bash
./huffman -c input.txt
./huffman -c input.txt compressed.huff
```
2. File decompression
```bash
./huffman -d compressed.huff
./huffman -d compressed.huff output.txt
```
