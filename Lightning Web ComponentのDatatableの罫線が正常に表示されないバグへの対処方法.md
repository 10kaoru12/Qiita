# Lightning Web Component(LWC)で正常に罫線が表示されないバグ

バグなのか自分の実装方法が悪いのか、lightning web component標準のlightning-datatableを使うと正常に罫線が表示されてくれない。
筆者が現状確認できているバグ（？）とソリューションを考えた。
もしこの状況がバグでなく公式なソリューションを知っている方は教えて欲しい。

## バグの概要

1. lightning-datatableで実装してx軸スクロールすると一部の罫線が途切れる。下の画像のsample4とsample5の間で罫線が切れていることがわかる。
<img width="839" alt="スクリーンショット 2020-02-13 19.34.08.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/ac87ffb0-c128-5ef2-8b9b-f6210c379d7f.png">

2. lightning-datatableでslds-table_col-borderedを実装しようとすると一列目だけ罫線が表示されない
<img width="839" alt="スクリーンショット 2020-02-13 19.43.17.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/4e0df32b-4c4e-f157-501f-405e34fbe70f.png">

## lightning web component標準のdatatableを実装したソースコード

1のソース

```html
<template>
    <div class="slds-table_col-bordered">
        <lightning-datatable data={sorted_data} columns={columns} key-field="id" sorted-by={sorted_by}
            onsort={handle_sort_data} sorted-direction={sorted_direction}>
        </lightning-datatable>
    </div>
</template>
```

```javascript
import { LightningElement, track } from 'lwc';

const columns = [
    { label: 'sample1', fieldName: 'sample1', type: 'text', sortable: true, fixedWidth: 200 },
    { label: 'sample2', fieldName: 'sample2', type: 'date', sortable: true, fixedWidth: 200 },
    { label: 'sample3', fieldName: 'sample3', type: 'percent', sortable: true, fixedWidth: 200 },
    { label: 'sample4', fieldName: 'sample4', type: 'currency', sortable: true, fixedWidth: 200 },
];

const data = [
    { sample1: 'sample3', sample2: '2020-01-10', sample3: 0.784, sample4: 321456 },
    { sample1: 'sample1', sample2: '2020-01-15', sample3: 0.3248, sample4: 3214 },
    { sample1: 'sample5', sample2: '2020-01-20', sample3: 0.321149, sample4: 356 },
    { sample1: 'sample3', sample2: '2020-01-2', sample3: 0.149, sample4: 35644444 },
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

    sort_data(fieldname, direction) {
        let sorting_data = JSON.parse(JSON.stringify(this.sorted_data));
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

2 のソース

```html
<template>
    <lightning-datatable data={sorted_data} columns={columns} key-field="id" sorted-by={sorted_by}
        onsort={handle_sort_data} sorted-direction={sorted_direction}>
    </lightning-datatable>
</template>
```

```javascript
import { LightningElement, track } from 'lwc';

const columns = [
    { label: 'sample1', fieldName: 'sample1', type: 'text', sortable: true, fixedWidth: 200 },
    { label: 'sample2', fieldName: 'sample2', type: 'date', sortable: true, fixedWidth: 200 },
    { label: 'sample3', fieldName: 'sample3', type: 'percent', sortable: true, fixedWidth: 200 },
    { label: 'sample4', fieldName: 'sample4', type: 'currency', sortable: true, fixedWidth: 200 },
    { label: 'sample5', fieldName: 'sample5', type: 'text', fixedWidth: 200 },
    { label: 'sample6', fieldName: 'sample6', type: 'date', fixedWidth: 200 },
    { label: 'sample7', fieldName: 'sample7', type: 'percent', fixedWidth: 200 },
    { label: 'sample8', fieldName: 'sample8', type: 'currency', fixedWidth: 200 },
    { label: 'sample9', fieldName: 'sample9', type: 'text', fixedWidth: 200 },
    { label: 'sample10', fieldName: 'sample10', type: 'date', fixedWidth: 200 },
    { label: 'sample11', fieldName: 'sample11', type: 'percent', fixedWidth: 200 },
    { label: 'sample12', fieldName: 'sample12', type: 'currency', fixedWidth: 200 },
    { label: 'sample13', fieldName: 'sample13', type: 'text', fixedWidth: 200 },
    { label: 'sample14', fieldName: 'sample14', type: 'date', fixedWidth: 200 },
    { label: 'sample15', fieldName: 'sample15', type: 'percent', fixedWidth: 200 },
    { label: 'sample16', fieldName: 'sample16', type: 'currency', fixedWidth: 200 },
];

const data = [
    { sample1: 'sample3', sample2: '2020-01-10', sample3: 0.784, sample4: 321456, sample5: 'sample', sample6: '2020-01-10', sample7: 50, sample8: 321456, sample9: 'sample', sample10: '2020-01-10', sample11: 50, sample12: 321456, sample13: 'sample', sample14: '2020-01-10', sample15: 50, sample16: 321456 },
    { sample1: 'sample1', sample2: '2020-01-15', sample3: 0.3248, sample4: 3214, sample5: 'sample', sample6: '2020-01-10', sample7: 50, sample8: 321456, sample9: 'sample', sample10: '2020-01-10', sample11: 50, sample12: 321456, sample13: 'sample', sample14: '2020-01-10', sample15: 50, sample16: 321456 },
    { sample1: 'sample5', sample2: '2020-01-20', sample3: 0.321149, sample4: 356, sample5: 'sample', sample6: '2020-01-10', sample7: 50, sample8: 321456, sample9: 'sample', sample10: '2020-01-10', sample11: 50, sample12: 321456, sample13: 'sample', sample14: '2020-01-10', sample15: 50, sample16: 321456 },
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

    sort_data(fieldname, direction) {
        let sorting_data = JSON.parse(JSON.stringify(this.sorted_data));
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

## ソリューション

1. この場合の問題点は、x軸方向にスクロールした場合にのみ発生するので、そもそもスクロールしないようなdatatableであればLightning Web Component標準のdatatableを使用して良い

例としては、以下のような場合である。

<img width="839" alt="スクリーンショット 2020-02-13 19.52.19.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/11cb5adc-a0ab-8b86-4888-08991ac90e68.png">

だが、以下のようにカラムが増えすぎてスクロールしないと見れないような場合は他の手段を考えなければならない。

<img width="839" alt="スクリーンショット 2020-02-13 19.52.19.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/11cb5adc-a0ab-8b86-4888-08991ac90e68.png">

2. Lightning Design System(slds)のdatatableを使う

## 実演

以下のようにx軸スクロールも、罫線の途切れもなく実装できていることがわかる。

![bt469-kae9m.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/246162/ff5b3a7a-0018-7a79-56e5-e894521b70ac.gif)

## lightning design systemのdatatableを実装したソースコード

```html
<template>
    <div
        class="slds-table slds-table_cell-buffer slds-table_bordered slds-is-relative slds-table_col-bordered slds-scrollable --x">
        <table>
            <thead>
                <tr>
                    <th>
                        <div>sample2
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample2" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample2" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample3
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample3" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample3" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                    <th>
                        <div>sample1
                            <lightning-icon if:true={arrow_direction} icon-name="utility:arrowup" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                            <lightning-icon if:false={arrow_direction} icon-name="utility:arrowdown" size="x-small"
                                name="sample1" onclick={handleSort}>
                            </lightning-icon>
                        </div>
                    </th>
                </tr>
            </thead>
            <tbody>
                <template for:each={sorted_data} for:item="element">
                    <tr key={element.id} class="slds-hint-parent">
                        <td>
                            <div class="slds-truncate">
                                {element.sample1}
                            </div>
                        </td>
                        <td>
                            <div class="slds-truncate">
                                {element.sample2}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
                                {element.sample3}
                            </div>
                        </td>
                        <td>
                            <div>
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

```javascript
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

## 参考になるURL

- [Lightning datatable doesn't apply styling to 1st row in LWC.](https://salesforce.stackexchange.com/questions/285120/lighting-datatable-doesnt-apply-styling-to-1st-row-in-lwc)

- [lightning-datatableの公式ドキュメント](https://developer.salesforce.com/docs/component-library/bundle/lightning-datatable/documentation)

- [lightning design systemの公式ドキュメント](https://www.lightningdesignsystem.com/components/data-tables/)
