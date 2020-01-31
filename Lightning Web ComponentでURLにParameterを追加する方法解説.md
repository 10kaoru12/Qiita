# 概要

Lightning Web Componentで開発してる際、任意のsalesforce上のサイトにparameterを追加してnavigationしたい状況があり、実装したのでメモ

## ソース1（非推奨）

- 成功するソース

```html
<template>
    <div>
        <a href='https://環境コード.lightning.force.com/lightning/page/home?c__flag=0'>move</a>
    </div>
</template>
```

- 失敗するソース

```html
<template>
    <div>
        <a href='https://環境コード.lightning.force.com/lightning/page/home?flag=0'>move</a>
    </div>
</template>
```

## ソース2（推奨）

- 成功するソース

```html
<!-- sample.html -->
<template>
    <div>
        <a href={url} onclick={handleClick}>move</a>
    </div>
</template>
```

```js
//sample.js
import { LightningElement, track } from 'lwc';
import { NavigationMixin } from 'lightning/navigation';

export default class Data_send_to_component_parent extends NavigationMixin(LightningElement) {
    @track url;
    PageRef;

    connectedCallback() {
        this.PageRef = {
            type: 'standard__namedPage',
            attributes: {
                pageName: 'home'
            },
            state: {
                c__flag: '0'
            }
        };
        this[NavigationMixin.GenerateUrl](this.PageRef)
            .then(url => { this.url = url });
    }

    handleClick(evt) {
        evt.preventDefault();
        evt.stopPropagation();
        this[NavigationMixin.Navigate](this.PageRef, true);
    }
}
```

- 失敗するソース

```html
<!-- sample.html -->
<template>
    <div>
        <a href={url} onclick={handleClick}>move</a>
    </div>
</template>
```

```js
//sample.js
import { LightningElement, track } from 'lwc';
import { NavigationMixin } from 'lightning/navigation';

export default class Data_send_to_component_parent extends NavigationMixin(LightningElement) {
    @track url;
    PageRef;

    connectedCallback() {
        this.PageRef = {
            type: 'standard__namedPage',
            attributes: {
                pageName: 'home'
            },
            state: {
                flag: '0'
            }
        };
        this[NavigationMixin.GenerateUrl](this.PageRef)
            .then(url => { this.url = url });
    }

    handleClick(evt) {
        evt.preventDefault();
        evt.stopPropagation();
        this[NavigationMixin.Navigate](this.PageRef, true);
    }
}
```

## ソース1解説

ザ・ハードコーディング
navigationを使おう

## ソース2解説

1. lightning/navigationをインポートする。ここでは、NavigationMixinとして設定

2. インポートしたNavigationMixin関数をコンポーネントの基本クラスに適用

3. 遷移先のURLをthis[NavigationMixin.GenerateUrl](作成するURLの設定情報)で作成する
この時、this[NavigationMixin.GenerateUrl](作成するURLの設定情報)は、Promiseを返すので、thenメソッドでurlを受け取りtrackプロパティなどに格納してhtmlに渡すなどする。

4. onclickなどでfireした際のnavigationはthis[NavigationMixin.Navigate](this.PageRef, true)で行う。

## ナビゲーションするページ

this.pageRefで設定したページに飛ぶがtypeがいくつかあるので、遷移するURL別で紹介する。

- /cmp/{componentName}

```js
{
    type:"standard__component",
    attributes:{
        componentName:"c__MyLightningComponent"
    }
}
```

- /articles/{articleType}/{urlName}

```js
{
    type: "standard__knowledgeArticlePage",
    attributes: {
        articleType: "Briefings",
        urlName: "February-2017"
    }
}
```

- /page/{pageName}
ページの名前はこの様なものがある

  - home
  - chatter
  - today
  - dataAssessment
  - filePreview

```js
{
    type: "standard__namedPage",
    attributes: {
        pageName: "home"
    }
}
```

```js
{
    type: "standard__namedPage",
    attributes: {
        pageName: "chatter"
    }
}
```

- /n/{devName}

```js
{
    type: "standard__navItemPage",
    attributes: {
        apiName: "MyCustomTabName"
    }
}
```

- /o/{objectApiName}/{actionName}

```js
{
    type: "standard__objectPage",
    attributes: {
        objectApiName: "Account",
        actionName: "list"
    }
}
```

- /r/{objectApiName}/{recordId}/{actionName}
- /r/{recordId}/{actionName}

```js
{
       type: "standard__recordPage",
       attributes: {
           recordId: "001xx000003DGg0AAG",
           objectApiName: "PersonAccount",
           actionName: "view"
       }
}
```

- /r/{objectApiName}/{recordId}/related/{relationshipApiName}/{actionName}
- /r/{recordId}/related/{relationshipApiName}/{actionName}

```js
{
    type: "standard__recordRelationshipPage",
    attributes: {
        recordId: "500xx000000Ykt4AAC",
        objectApiName: "Case",
        relationshipApiName: "CaseComments",
        actionName: "view"
    }
}
```

## 結論

c__を付ければparameterとして認識する
parameterの値はstringでないと認識しない

## （追記）付加されたQuery Parameterを取得する方法

```js
connectedCallback() {
    const param = 'c__flag';
    const paramValue = this.getUrlParamValue(window.location.hrefwindow.location.href, param);
}

getUrlParamValue(url, key) {
    return new URL(url).searchParams.get(key);
}
```

図

とすると、この様に取得することができる。
調べた限りこれが一番簡単なParameterを取得する方法かなと思うが、もし他の良い方法があれば教えて欲しいです。

## 参考になるサイト

- [navigationについての公式ドキュメント]<https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.use_navigate_basic>
- [parameter追加に関する公式ドキュメント]<https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.use_navigate_add_params_url>
- [遷移先のtypeに関する公式ドキュメント簡易版]<https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.use_navigate_page_types>
- [遷移先のtypeに関する公式ドキュメント詳細]<https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.reference_page_reference_type>
- [遷移先のtypeに関するドキュメント日本語]<https://developer.salesforce.com/docs/atlas.ja-jp.lightning.meta/lightning/components_navigation_page_definitions.htm>
