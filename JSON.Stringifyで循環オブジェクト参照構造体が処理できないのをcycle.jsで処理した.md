# 概要

<https://qiita.com/saitoeku3/items/9e9a608e53029d541a8f>
と同じエラーにあったので、cycle.jsで処理したサンプルコードを紹介するよというお話

## cycle.js

<https://github.com/douglascrockford/JSON-js/blob/master/cycle.js>

## インストール

```bash
npm install json-cyclic
```

## サンプルコード

```js
//import
const decycle = require('json-decycle').decycle;
const retrocycle = require('json-decycle').retrocycle;
...

...
//文字列に変換
receiveNewAcString = JSON.stringify(receiveNewJson, decycle());

//JSONオブジェクトに変換
receiveNewAc = JSON.parse(receiveNewAcString, retrocycle()).data;
```
