# 概要

Lightning Web Componentで開発していて、カスタム要素を使用する時に詰まったのでメモしておく。

## エラー内容

```powershell-interactive
No MODULE named markup://salesforceから認識されているコンポーネント found : [markup://それに近そうなコンポーネント]
```

## カスタム要素の命名
コンポーネントの命名をする前に、他のコンポーネントでコンポーネントを使用する場合には、カスタム要素の先頭に「c-」をつける必要がある（名前空間）
「samplecomponent」の場合

```html
<template>
    <c-samplecomponent></c-samplecomponet>
</template>
```

## カスタム要素の命名（大文字編）
コンポーネントの名前に大文字を含む場合ハイフンを入れる必要がある。
「sampleComponent」の場合

```html
<template>
    <c-sample-component></c-sample-componet>
</template>
```

## カスタム要素の命名（アンダーバー編）
コンポーネントの名前にアンダーバー（_）を含む場合はそのままカスタム要素に入れる。 
「sample_component」の場合

```html
<template>
    <c-sample＿component></c-sample＿componet>
</template>
```

## 例
「sample_Component」

```html
<template>
    <c-sample＿-component></c-sample＿-componet>
</template>
```
「sampleCOMPONENT」

```html
<template>
    <c-sample-c-o-m-p-o-n-e-n-t></c-samplec-sample-c-o-m-p-o-n-e-n-t>
</template>
```

## まとめ
コンポーネントの名前に大文字を連続させると面倒なことになるので小文字で完結できるような命名規則にするといい

## 参考
- [Lightning Web コンポーネントの作成](https://trailhead.salesforce.com/ja/content/learn/modules/lightning-web-components-for-aura-developers/compose-components?trail_id=build-lightning-web-components)
- [コンポーネントのHTMLファイル](https://developer.salesforce.com/docs/component-library/documentation/ja-jp/lwc/lwc.create_components_html_file)
- [コンポーネントの名前空間](https://developer.salesforce.com/docs/component-library/documentation/ja-jp/lwc/lwc.create_components_namespace)