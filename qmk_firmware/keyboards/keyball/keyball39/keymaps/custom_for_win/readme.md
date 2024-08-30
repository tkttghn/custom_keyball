# Keyball39ファームウェア

tkttghnが自作したKeyball39のファームウェア。
片方のPromicroにはUS配列macOS用の"custom_for_mac"、もう一方にはJIS配列Windows用の"custom_for_windows"を書き込むことで、両OSに対応し、かつ違和感のない移行ができるようにする。

## 方針
1. LEDエフェクト無効化
1. OLEDの表示変更
1. レイヤー数の増加
1. AML(Auto Mouse Layer)の有効化
1. Windowsにおけるキーボード設定がJISの場合にもUS配列と同様の入力を実現
1. Windowsにおけるトラックボール動作の反転


## 補足
LEDはカスタムするとProMicroのメモリが枯渇するので除外する（そもそも個人的にLEDモジュール搭載してない）