def rc4_encrypt(data, key):
    S = list(range(256))
    j = 0

    # Key-scheduling algorithm (KSA)
    for i in range(256):
        j = (j + S[i] + key[i % len(key)]) % 256
        S[i], S[j] = S[j], S[i]

    # Pseudo-random generation algorithm (PRGA) & encryption
    i = j = 0
    result = bytearray()
    for byte in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        k = S[(S[i] + S[j]) % 256]
        result.append(byte ^ k)

    return result

def main():
    # 原始的payload（cale.exe）
    payload = b"你的shellcode"
    # 加密密钥
    key = b"thisIsA16ByteKey"  # 16字节密钥

    # 使用RC4算法加密payload
    encrypted_payload = rc4_encrypt(payload, key)

    # 将加密的payload写入文件
    with open("result.txt", "wb") as file:
        file.write(encrypted_payload)

    print("加密后的payload已写入result.txt")

if __name__ == "__main__":
    main()
