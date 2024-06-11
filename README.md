# C_Sep_Loader

## Introduce

一个简单的远程分离的加载器,免杀国内大部分杀软

## How to use

修改Encryption/payload_c_x64.py的24行，改为自己的shellcode

运行python脚本（环境python3.6）

将生成的result.txt上传到Web端（Oss,跳板等机器）

copy自己的地址如http://example.org

将http://example.org 替换 ShellCodeLoader/Source.c 的152行，生成64位发行版即可

## Test
![Untitled 1](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/759f6998-71ff-4a03-abd9-71fb40cc7eeb)
![Untitled 2](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/98f20b30-548a-4980-be96-c8886ce8956e)
![Untitled](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/8de5f3b4-ee6b-4ea7-b52d-2c3f2ce0c553)


## ps
此项目为开源项目，仅提供与学习。请勿用于违法行为，造成的违法行为与本人无关。

