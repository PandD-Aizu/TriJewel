# TriJewel
2021年度学祭へ展示するパズルゲーム制作プロジェクトです。

## 初期設定
- 方法1
  1. VisualStudioを開く
  2. 右側にある「リポジトリのクローン(C)」を選択
  3. リポジトリの場所(R)に「https://github.com/PandD-Aizu/TriJewel 」を入力
  4. ローカル パス(L)に作業ディレクトリのパスを入力して、左下のクローンをクリック
      - 作業ディレクトリは空にしておいてください
  6. コマンドプロンプトを開き、作業ディレクトリまで移動する
      - 以降は、作業ディレクトリでgitコマンドが使えます
  7. 以下のコマンドを入力する
      - [自分のハンドルネーム]には、PandDで使っているハンドルネームを入れてください
      - できればアルファベットでお願いします
```
git branch [自分のハンドルネーム]
git checkout [自分のハンドルネーム]
git pull origin main
```

- 方法2
  1. コマンドプロンプトを開き、作業ディレクトリまで移動する
      - 作業ディレクトリは空にしておいてください
  2. 以下のコマンドを入力する
      - [自分のハンドルネーム]には、PandDで使っているハンドルネームを入れてください
      - できればアルファベットでお願いします
```
git init
git clone https://github.com/PandD-Aizu/TriJewel
git branch [自分のハンドルネーム]
git checkout [自分のハンドルネーム]
git pull origin main
```
**作業は、自分のブランチで行うようにしてください。**

## 変更を適用する
コマンドプロンプトで以下のコマンドを入力してください。
```
git add [変更を加えたファイル]
git commit -m "コメント"
git push origin [自分のハンドルネーム]
```
**merge関連はKENnYがまとめてやっておきます。**
