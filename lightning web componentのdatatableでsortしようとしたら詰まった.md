# lightning-datatableでソートするには

## 罠

<https://developer.salesforce.com/docs/component-library/bundle/lightning-datatable/documentation>
によると、

```js
        // The method onsort event handler
        updateColumnSorting(event) {
            var fieldName = event.detail.fieldName;
            var sortDirection = event.detail.sortDirection;
            // assign the latest attribute with the sorted column fieldName and sorted direction
            this.sortedBy = fieldName;
            this.sortedDirection = sortDirection;
            this.data = this.sortData(fieldName, sortDirection);
       }
```

で完成しそうであるかのように書いてあるが、これが罠で、sortDataメソッドを作成する必要がある。
んじゃ、sortDataはどう作ればいいのというと、aura componentのドキュメントにsortDataの中身の記載がある。

<https://developer.salesforce.com/docs/component-library/bundle/lightning:datatable/documentation>

```js
({
    sortData: function (cmp, fieldName, sortDirection) {
        var data = cmp.get("v.data");
        var reverse = sortDirection !== 'asc';
        //sorts the rows based on the column header that's clicked
        data.sort(this.sortBy(fieldName, reverse))
        cmp.set("v.data", data);
    },
    sortBy: function (field, reverse, primer) {
        var key = primer ?
            function(x) {return primer(x[field])} :
            function(x) {return x[field]};
        //checks if the two rows should switch places
        reverse = !reverse ? 1 : -1;
        return function (a, b) {
            return a = key(a), b = key(b), reverse * ((a > b) - (b > a));
        }
    }
})
```

## サンプルコード

auraのコードしか載ってないじゃん、lightning web componentでどう作るんですか？
という私のコピーみたいな人のためにサンプルコードをあげておきます。


```js
    sort_data(fieldname, direction) {
        let sorting_data = JSON.parse(JSON.stringify(data));

        let keyValue = (a) => {
            return a[fieldname];
        };

        let isReverse = direction === 'asc' ? 1 : -1;

        sorting_data.sort((x, y) => {
            x = keyValue(x) ? keyValue(x) : '';
            y = keyValue(y) ? keyValue(y) : '';

            return isReverse * ((x > y) - (y > x));
        });
        this.data = sorting_data;
    }
```

## 注意

このヘルパー関数でソートする際に注意点があり、日付のfieldでソートする場合は、

```js
const data = [{
    last_login: '2019-10-10'
}
```

このような形式にする必要がある。
筆者は、

```js
const data = [{
    last_login: '2019/10/10'
}
```

このようにしてソート機能が正常に動かないバグに10時間くらい時間を食われたので、参考までに…。

## 追記

salesforceでのプログラミングをする際は必ずsalesforceのフォーマットに合わせたデータを作らないと正常に動作しないので、必ず、salesforceでどのようなフォーマットが使われているのかを調査したのちにプログラムを作ることをオススメする。
主に、コンポーネントで使われるフォーマットはそのコンポーネントのドキュメントに記載があるので、参照すると良い。
