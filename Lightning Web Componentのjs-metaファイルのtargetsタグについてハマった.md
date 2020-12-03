# 概要
Lightning Web Component内のコンポーネント名.js-meta.xmlと言うファイルのデプロイ先を指定するtargetsタグでエラーが出たのでメモ

## エラー
今回のエラーはlightningCommunityにコンポーネントをデプロイしたい場合

```powershell
lightningCommunity_Page is not a valid TARGETS
```

##　エラー対象のtargets設定
```xml
<?xml version="1.0" encoding="UTF-8"?>
<LightningComponentBundle xmlns="http://soap.sforce.com/2006/04/metadata">
    <apiVersion>50.0</apiVersion>
    <isExposed>true</isExposed>
    <targets>
        <target>lightningCommunity_Page</target>
    </targets>
</LightningComponentBundle>
```

## 正しいtargets設定

```xml
<?xml version="1.0" encoding="UTF-8"?>
<LightningComponentBundle xmlns="http://soap.sforce.com/2006/04/metadata">
    <apiVersion>50.0</apiVersion>
    <isExposed>true</isExposed>
    <targets>
        <target>lightningCommunity__Page</target>
    </targets>
</LightningComponentBundle>
```

## まとめ
アンダーバーが2つ必要