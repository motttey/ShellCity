# ShellCity
ncursesで動くSim Cityみたいなゲーム
#使用方法
上述のプログラムを構成するファイル群のあるディレクトリで"make run"コマンドにより実行
"make" コマンドによりShell Cityをコンパイル
"make clean"コマンドにより実行ファイル群を削除

##詳細
Shell Cityはncursesライブラリを用いて作成したEA Japanによるシミュレーションゲーム「シムシティ」のパロディゲームである。

Shell Cityの実行画面はマップ画面とメッセージや操作方法を表示する画面に別れ、ユーザはシェル上に展開されたマップ上にエリアを配置し、町を作成できる。

#画面構成#
Shell Cityは以下の5つの画面から構成される。
- Start Screen:ゲーム開始時に表示される画面

- Main Screen:ゲーム画面

- GameOver Screen:ゲームオーバー時に表示される画面

- GameClear Screen:ゲームクリア時に表示される画面

- Option Screen:コマンドの説明が表示される画面

Shell Cityは主に予算と人口というパラメータをもとに、都市を発展させる。

予算と人口は各エリアの隣接関係や全体的な比率に基づいて計算される。ただし、予算は歳入額が毎ターン加算される形で計算される。


#エリア


Shell Cityでは、マップ画面に各エリアを配置する。
配置されたエリアの数や種類にもとづき、歳入額が計算される。
各エリアの種類には以下のようなものがある。
- 住宅地(緑色):住宅地を表すエリア。
- 商業地(青色):商業地を表すエリア。隣接する住宅地の歳入額に好影響を及ぼす。
- 工業地帯(黄色):工業地帯を表すエリアです。隣接する住宅地の歳入額に悪影響を及ぼす。
- 公共施設(白色):公共施設イベント時のみ建設可能、コストがかかる。
- 水(水色):ゲーム開始時にいくつかのパターンから描画される。住宅や商業地に対して好影響を及ぼす。
- 高級住宅地(明るい緑色):特定の条件を満たした時のみ建造できる住宅地エリア
- 高級商業地(明るい青色):特定の条件を満たした時のみ建造できる商業地エリア
- ハイテク工業地帯(明るい黄色):特定の条件を満たした時のみ建造できる工業地帯エリア

また、住宅地・商業地・工業地帯のそれぞれの数の差が5以上のとき、歳入は半減する。(バランスよく建造する必要あり)


#イベント
主に人口をトリガとしてイベントが生じる場合がある。

##公共施設
人口が一定以上に達すると、画面右下に公共施設の建設を促すメッセージが表示される。
この時、公共施設を建設するまでゲームは進行しない。また、公共施設建設後は、公共施設の維持費が毎ターン必要になる。
各公共施設イベントが出現する条件は以下のとおり。
　- 警察(Police):人口が50の倍数
  - 消防署(Firehouse):人口が100の倍数
  - 病院(Hospital):人口が200の倍数
  - 刑務所(Jail):人口が500の倍数


#ゲームクリア/ゲームオーバー条件


##ゲームクリア条件
- マップ上の全領域のエリアタイプが0でないとき
- 予算が一定額(100000000)を超えた時
##ゲームオーバー条件
- 予算がマイナスになったとき

#Commands List

##Common Commands

- q:終了 (on Start,Main,Gameover,Gameclear,Option)
- s:開始 (on Start)
- r:ゲームの再開(on Gameover,GameClear)



##Main Commands


###動作コマンド(上下左右に動く)
- u:up

- h:left

- j:down

- k:right

###建設コマンド

- t:住宅地の建設 (Cost is $300)

- s:商業地の建設 (Cost is $500)

- f:工業地帯の建設 (Cost is $400)

- Shift + p:公共施設の建設 (公共施設イベント時のみ)

- d:エリアの削除(エリア情報が削除される)


###その他

- o:オプション画面を表示




##Hidden Commands



以下の3つのコマンドは人口が1000人を超えたときのみ実行可能

　- Shift + t:高級住宅地の建設 (Cost is $1000)
  - Shift + s:高級商業地の建設 (Cost is $1500)

  - Shift + f:ハイテク工業地帯の建設(Cost is $1300)

##デバッグ用コマンド
m:予算を強制的に増加しゲームクリア画面へ遷移する
