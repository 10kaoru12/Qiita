# 概要

lightning web component(lwc)のlightning-spinnerをcomponentサイズでのloading(lightning-spinner)がしたいのに、full pageサイズでloading(lightning-spinner)してしまう問題に直面したのでメモ
lightning web component(lwc)のlightning-spinnerを普通に使うと画面全体がspinnerでグルグルしてしまう。

![images.jpeg](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/04a7d70c-ce55-8524-a62f-4456284f1d17.jpeg)

理想としては以下の様にしたい

![NQIra.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/92fdb40d-0586-763e-4993-158f0b6f5682.png)

## 結論

結論としては、lightning web component標準のタグの中でlightning-spinnerを動作させることはできないことがわかった。
代用策として、lightning design systemのタグの中にlightning-spinnerを入れることでcomponentサイズでのloading(lightning-spinner)を実装することができた。

## ソース

- buttonの中でloading(lightning-spinner)を動作させる例

```html
<div class="slds-button slds-button_brand">
    <lightning-spinner alternative-text="loading..."></lightning-spinner> //alternative-textを入れないと警告が出るので入れる
</div>
```

- buttonの中でloading(lightning-spinner)を動作しない例

```html
<lightning-button label="sample">
    sample
    <lightning-spinner alternative-text="loading..."></lightning-spinner>
</lightning-button>
```

- select-boxで動作させる例

```html
<div class="slds-form-element slds-grid slds-wrap">
    <c-lightning_spinner alternative-text="loading..."></c-lightning_spinner>
    <div class="slds-select_container slds-size_2-of-2">
        <select class="slds-select" name="optionSelect">
            <option value="sample">sample</option>
        </select>
</div>
```

## 参考

<https://salesforce.stackexchange.com/questions/279270/how-to-include-spinner-in-button-in-lwc>
