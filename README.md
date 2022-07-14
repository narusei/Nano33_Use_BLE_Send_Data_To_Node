# Nano33_Use_BLE_Send_Data_To_Node

Nano33 を用いた BLE を使用して加速度センサのデータを送信するプログラムです。

## 用意するもの

- Nano33BLE
- BLE 経由で接続できるロガー
  - [Blegger](https://github.com/narusei/blegger) というロガーを作成しましたのでご活用ください

## 使い方

1. 本リポジトリをお好きな場所へ Clone します
2. Nano33BLE にスケッチを書き込みます

## 各種設定について

- SERVICE_UUID = "92c25488-dcbc-11ec-9d64-0242ac120002"
- Acceleration_Characteristic_UUID = "97e480da-dcbc-11ec-9d64-0242ac120002"
- Gyroscope_Characteristic_UUID = "dc5d8910-dcca-11ec-9d64-0242ac120002"
- LocalNAME = "IMUMonitor"
- DeviceNAME = "nano33BLE"
