#########################################################################
# File Name: manage.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2022年10月19日 星期三 10时10分05秒
#########################################################################
#!/bin/bash
CurDir=$(pwd)
case $1 in
mine)	
	ls $Curdir
	;;
largest)
	ls -l $Curdir | sort -nr -k5 |head -1|awk '{printf $9 "\0"}'
	;;
*)
	echo "not available"
	echo "Please use -mine or -largest"
	;;
esac
