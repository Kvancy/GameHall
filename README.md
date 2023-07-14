# GameHall
## 有待完善：

1. 按钮弹起和落下bug有待修复
2. Gamehall的UI界面有待美化
3. 增加右键点击游戏可以实现小菜单（卸载游戏或者下载游戏）的功能
4. 本地没有的游戏可以提供下载链接让用户选择性下载（需要另外窗口显示下载进度）
5. 增加社交功能，例如好友，社区等
6. 优化窗口最大化显示界面
7. 窗口边框有待美化

## 开发日志：

- 2023/6/9：完成Gamehall的界面基本布局
- 2023/6/13：完成gif的正常播放并放置控制播放按钮，实现左右循环播放
- 2023/6/19：构成hallbtn类，并实现游戏按钮的弹起落下效果

- 2023/6/24：基本实现了排行榜功能，用户可以点击排行榜进入游戏

- 2023/6/29：提供了上传头像的接口，对传输的文件进行检测，检测成功在数据库中保存图片格式，二进制文件，从而实现用户再次登录时显示之前上传的图片。

- 2023/7/2：增加了返回Home按钮，实现返回大厅主界面功能。

- 2023/7/6：基本实现了游戏搜索功能，可以对输入关键字进行包含检测，然后做出相应显示。

- 2023/7/9：增加了用户通过邮箱注册功能，并对邮箱的输入进行必要检测，利用定时器实现60秒后才可重新发送功能。
