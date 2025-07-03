@echo off
rem 添加所有更改到暂存区
git add .

rem 提交更改，并附带提交信息
git commit -m "update"

rem 强制推送到远程仓库的指定分支
rem 注意：使用 -f (force) 选项需要谨慎，因为它会覆盖远程仓库的历史记录。
git push -f detect_of_vioce main

echo Git操作完成：已添加、提交并强制推送到 detect_of_vioce/main。
pause