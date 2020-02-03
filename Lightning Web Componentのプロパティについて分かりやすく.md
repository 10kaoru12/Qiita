# 概要

Lightning Web Componentの（LWC)プロパティ定義が難しかったので、分かりやすい情報とソースコードをまとめた。

## LWCのプロパティの種類

- track
- api
- wire

## Salesforceのデコレータ早分かり図

terraskyさんが分かりやすい図を作っていただいているので、それを載せると共に詳しく記載されているURLも載せます。
<https://base.terrasky.co.jp/articles/zpT4b>

図

## track

コンポーネント内のHTMLとJavaScriptをリアクティブに連携するためのプロパティで、単方向バインディングの実装をできます。

### trackのサンプルコード

```html
<template>
    {hello}
</template>
```

```js
import { LightningElement, track } from 'lwc';

export default class Decorator extends LightningElement {
    @track
    hello = "hello world!";
}
```

### trackサンプルコード実行図

図

### trackのサンプルコード説明

この例では、@trackプロパティの変数helloにhello world!を代入してhtmlに値を渡しています。

## api

他のコンポーネント間でデータの送受信をする際に使用するプロパティで、@trackと併用することはできない。
以下では、子コンポーネント、親コンポーネントについて軽く説明する

- 子コンポーネント
親コンポーネントの中に含まれるコンポーネント

- 親コンポーネント
子コンポーネントを含むコンポーネント

### apiのサンプルコード

- 子コンポーネント

```html
<template>
    hello:{item}
</template>
```

```js
import { LightningElement, api } from 'lwc';

export default class Data_send_to_component_child extends LightningElement {
    @api item;
}
```

- 親コンポーネント

```html
<template>
    <lightning-input onchange={handler}></lightning-input>
    <c-data_send_to_component_child item={value}></c-data_send_to_component_child>
</template>
```

```js
import { LightningElement, track } from 'lwc';

export default class Data_send_to_component_parent extends LightningElement {
    @track value;

    handler(event) {
        this.value = event.detail.value;
    }
}
```

### apiサンプルコード実行図

図

### apiのサンプルコード説明

1. 子コンポーネントで@apiプロパティの変数itemを公開

2. 親コンポーネントにて<c-（コンポーネント名）>を使って子コンポーネントを表示

3. 親コンポーネント内でinputのイベントハンドラーを使用して双方向バインディングを実装

4. バインディングした値を子コンポーネントに渡す（item={value})

## wire
