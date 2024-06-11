# C_Sep_Loader

## Introduce

一个简单的远程分离的加载器

## How to use

修改Encryption/payload_c_x64.py的24行，改为自己的shellcode

运行python脚本（环境python3.6）

将生成的result.txt上传到Web端（Oss,跳板等机器）

copy自己的地址如http://example.org

将http://example.org替换**ShellCodeLoader/Source.c的152行，生成64位发行版即可**

## Test

![Untitled](C_Sep_Loader%208dcd4f04e7e941a480b9ed1d1b3ef0a8/Untitled.png)

![Untitled](C_Sep_Loader%208dcd4f04e7e941a480b9ed1d1b3ef0a8/Untitled%201.png)

![Untitled](C_Sep_Loader%208dcd4f04e7e941a480b9ed1d1b3ef0a8/Untitled%202.png)

## ps

此项目为开源项目，仅提供与学习。请勿用于违法行为，造成的违法行为与本人无关。
