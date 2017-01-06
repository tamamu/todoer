# Todoer

コマンドラインTODO管理ツール

コマンドラインで動作するTODO管理ツールです。  
タイムカプセル(2012)に埋まってたUSBメモリに保管されていたのでとりあえず保存。

conkyと併用して使うことを想定していました。  

## Usage

```bash
Compile
$ make

Show help
$ ./todoer -h

Show all tasks
$ ./todoer -a

Show running tasks
$ ./todoer -i

Update all tasks
$ ./todoer -u

Add task
$ ./todoer add buy "TOEIC Training book"

Add task with deadline
$ ./todoer add go "The Eiffel Tower" 2017/8/21

Remove task2
$ ./todoer delete 2

Complete task3
$ ./todoer comp 3
```