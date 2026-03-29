#include <iostream>
#include <windows.h>
#ifdef WIN_32
// Function to execute
typedef void(*FuncPtr)();

int main() {
    // Step 1: Allocate executable memory
    SIZE_T size = 1024; // Allocate 1 KB
    void* execMemory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (execMemory == NULL) {
        std::cerr << "VirtualAlloc failed: " << GetLastError() << std::endl;
        return 1;
    }

    // Step 2: Write some machine code to the allocated memory
    // This example will write a simple function that returns
    unsigned char code[] = {
        0xC3 // RET instruction (x86 machine code)
    };

    memcpy(execMemory, code, sizeof(code));

    // Step 3: Cast the memory to a function pointer and call it
    FuncPtr func = reinterpret_cast<FuncPtr>(execMemory);
    func(); // Call the function

    // Step 4: Free the allocated memory
    if (!VirtualFree(execMemory, 0, MEM_RELEASE)) {
        std::cerr << "VirtualFree failed: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
#endif
#ifdef LINUX
#include <stdio.h>
#include <sys/mman.h>

typedef unsigned (*asmFunc)(void);

int main(int argc, char *argv[])
{
   // probably needs to be page aligned...

   unsigned int codeBytes = 4096;
   void * virtualCodeAddress = 0;

   virtualCodeAddress = mmap(
       NULL,
       codeBytes,
       PROT_READ | PROT_WRITE | PROT_EXEC,
       MAP_ANONYMOUS | MAP_PRIVATE,
       0,
       0);

   printf("virtualCodeAddress = %p\n", virtualCodeAddress);

   // write some code in
   unsigned char * tempCode = (unsigned char *) (virtualCodeAddress);
   tempCode[0] = 0xb8;
   tempCode[1] = 0x00;
   tempCode[2] = 0x11;
   tempCode[3] = 0xdd;
   tempCode[4] = 0xee;
   // ret code! Very important!
   tempCode[5] = 0xc3;

   asmFunc myFunc = (asmFunc) (virtualCodeAddress);

   unsigned out = myFunc();

   printf("out is %x\n", out);

   return 0;
}

#endif

