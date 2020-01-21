# 概要

lightning web component開発にてsalesforcedx cli上ではエラーが出ないのにいざsalesforce上のアプリケーションビルダーなどで閲覧するとcomponentが表示されない現象に悩まされたが解決したのでメモ

## 解決法

デフォルトで

```bash
SFDX:Create Lightning Web Component
```

コマンド又は、

```bash
sfdx force:lightning:component:create --type lwc --componentname example --outputdir force-app/main/default/lwc
```

などとすると、exampleディレクトリが作成されるとともに、

-example.html
-example.js
-example.js-meta.xml
が作成される。

この時のexample.js-meta.xmlにデプロイした後salesforce上のどのアプリケーションで表示させるかを指定する。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<LightningComponentBundle xmlns="http://soap.sforce.com/2006/04/metadata">
    <apiVersion>47.0</apiVersion>
    <isExposed>false</isExposed>
</LightningComponentBundle>
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<LightningComponentBundle xmlns="http://soap.sforce.com/2006/04/metadata">
    <apiVersion>47.0</apiVersion>
    <isExposed>true</isExposed>
    <targets>
        <target>lightning__AppPage</target>
        <target>lightning__RecordPage</target>
        <target>lightning__HomePage</target>
    </targets>
</LightningComponentBundle>
```

などとコンポーネントを表示するターゲットをxml上で明記する必要がある。

## 参考になるページ

### js-meta.xmlについて

- <https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.create_components_meta_file>
- <https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.reference_configuration_tags>

### salesforce Lightningアプリケーションビルダーでデプロイする場合

- <https://developer.salesforce.com/docs/component-library/documentation/lwc/lwc.use_config_for_app_builder>
