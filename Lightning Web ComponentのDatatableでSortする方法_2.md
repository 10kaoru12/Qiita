# 概要

Lightning Web Componentでプログラミングしている最中にLightning Web ComponentのDatatableを使ってソート機能を実装したい状況があり、その時に詰まったのでメモ

## 実演

![olg75-aufqk.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/11330b36-2c8c-2630-946b-cda18b9e3799.gif)

## ソース

```html
<template>
    <lightning-datatable data={sorted_data} columns={columns} key-field="id" sorted-by={sorted_by}
        onsort={handle_sort_data} sorted-direction={sorted_direction}>
    </lightning-datatable>
</template>
```

```js
import { LightningElement, track } from 'lwc';

const columns = [
    { label: 'sample1', fieldName: 'sample1', type: 'text', sortable: true },
    { label: 'sample2', fieldName: 'sample2', type: 'date', sortable: true },
    { label: 'sample3', fieldName: 'sample3', type: 'percent', sortable: true },
    { label: 'sample4', fieldName: 'sample4', type: 'currency', sortable: true },
];

const data = [
    { sample1: 'sample3', sample2: '2020-01-10', sample3: 0.784, sample4: 321456 },
    { sample1: 'sample1', sample2: '2020-01-15', sample3: 0.3248, sample4: 3214 },
    { sample1: 'sample5', sample2: '2020-01-20', sample3: 0.321149, sample4: 356 }
]

export default class Qiita_sample_code_2 extends LightningElement {
    @track sorted_data = data;
    @track columns = columns;
    @track sorted_by;
    @track sorted_direction;

    handle_sort_data(event) {
        this.sorted_by = event.detail.fieldName;
        this.sorted_direction = event.detail.sortDirection;
        this.sort_data(event.detail.fieldName, event.detail.sortDirection);
    }

    //実際にソートしてる関数
    sort_data(fieldname, direction) {
        let sorting_data = JSON.parse(JSON.stringify(this.sorted_data));
        // ソートするカラムの値を参照
        let keyValue = (a) => {
            return a[fieldname];
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
