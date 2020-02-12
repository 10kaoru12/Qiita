# 概要

Lightning Web Componentでプログラミングしている最中にLightning Design System内のDatatableを使ってソート機能を実装したい状況があり、その時に詰まったのでメモ

## 実演

![dbv38-wlkb8.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/cfb163fc-1b96-54d4-5d5c-e304a8f244b2.gif)

## やっていること

1. クリックハンドラー内で入っているデータのソートする。

2. for:eachでソートされているデータが格納されているオブジェクトを舐める

（iteratorでもできる）

## ソース

```html
<template>
    <div>
        <table class="slds-table slds-table_cell-buffer slds-table_bordered slds-table_col-bordered">
            <thead>
                <tr>
                    <th class="slds-size_1-of-3">
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th class="slds-size_1-of-3">
                        <div>sample2
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample2" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample2" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th class="slds-size_1-of-3">
                        <div>sample3
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample3" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample3" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                </tr>
            </thead>
            <tbody>
                <template for:each={sorted_data} for:item="element">
                    <tr key={element.id} class="slds-hint-parent slds-size_1-of-1">
                        <td class="slds-size_1-of-3">
                            <div class="slds-truncate">
                                {element.sample1}
                            </div>
                        </td>
                        <td class="slds-size_1-of-3">
                            <div class="slds-truncate">
                                {element.sample2}
                            </div>
                        </td>
                        <td class="slds-size_1-of-3">
                            <div class="slds-truncate">
                                {element.sample3}
                            </div>
                        </td>
                    </tr>
                </template>
            </tbody>
        </table>
    </div>
</template>
```

```js
import { LightningElement, track } from 'lwc';

//単純にstringとしてソートしているためか日付の場合zero paddingが必須
const data = [
    { id: 1, sample1: '2020-10-01', sample2: 123132321, sample3: 'a' },
    { id: 2, sample1: '2020-10-02', sample2: 6544566, sample3: 'b' },
    { id: 3, sample1: '2020-10-03', sample2: 98744166, sample3: 'c' },
    { id: 4, sample1: '2020-10-04', sample2: 8716555, sample3: 'd' },
    { id: 5, sample1: '2020-10-05', sample2: 498743, sample3: 'e' },
    { id: 6, sample1: '2020-10-06', sample2: 41688446, sample3: 'c' },
    { id: 7, sample1: '2020-10-07', sample2: 4687, sample3: 'e' },
    { id: 8, sample1: '2020-10-08', sample2: 4687, sample3: 'd' },
    { id: 9, sample1: '2020-10-09', sample2: 7763734, sample3: 'b' },
    { id: 10, sample1: '2020-10-10', sample2: 468743, sample3: 'a' },
];


export default class activity_log extends LightningElement {
    @track sorted_data = [];
    sort_direction = 'asc';
    sort_column = 'sample1';

    get arrow_direction() {
        return this.sort_direction === 'asc' ? true : false;
    }

    connectedCallback() {
        this.sorted_data = data;
        this.sort_data(this.sort_column, this.sort_direction);
    }

    // カラムのクリックハンドラー
    handleSort(event) {
        this.sort_direction = (this.sort_direction === 'asc') ? 'desc' : 'asc';
        this.sort_column = event.target.name;
        this.sort_data(this.sort_column, this.sort_direction);
    }

    //実際にソートしてる関数
    sort_data(sort_column, direction) {
        // JSON化しないとリアクティブにdatatableに反映されない
        let sorting_data = JSON.parse(JSON.stringify(this.sorted_data));

        // ソートするカラムの値を参照
        let keyValue = (a) => {
            return a[sort_column];
        };

        let isReverse = direction === 'asc' ? 1 : -1;

        sorting_data.sort((x, y) => {
            x = keyValue(x) ? keyValue(x) : '';
            y = keyValue(y) ? keyValue(y) : '';
            return isReverse * ((x > y) - (y > x));
        });

        this.sorted_data = sorting_data;
    }
}
```
