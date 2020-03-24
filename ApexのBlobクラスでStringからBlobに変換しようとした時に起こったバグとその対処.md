# 概要

ある文字列を暗号化してURLにパラメーターとして付与し、別ページでURLのパラメーターを受け取り復号化したいという状況

この際に、StringからBLOb(Binary Large Object)に変換する際、エンコード方式に制限があるようで、
「BLOB is not a valid UTF-8 string」
というエラーが出た。
その時の対処について記載する。

## エラーの発生したソースコード

```java
    Blob key=Crypto.generateAesKey(128);
    String encodedKey=key.toString();
    system.debug(encodedKey);
    Blob data=Blob.valueOf('00000');
    Blob encryptedData=Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData=EncodingUtil.base64Encode(encryptedData);
    system.debug(encodedEncryptedData);
    Blob decodedEncryptedData=EncodingUtil.base64Decode(encodedEncryptedData);
    Blob decrypted=Crypto.decryptWithManagedIV('AES128', key, decodedEncryptedData);
    String toStringData=decrypted.toString();
    system.debug(toStringData);
```

## 対処したソースコード

```java
    Blob key=Crypto.generateAesKey(128);
    String encodedKey=EncodingUtil.base64Encode(key);
    system.debug(encodedKey);
    Blob data=Blob.valueOf('00000');
    Blob encryptedData=Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData=EncodingUtil.base64Encode(encryptedData);
    system.debug(encodedEncryptedData);
    Blob decodedEncryptedData=EncodingUtil.base64Decode(encodedEncryptedData);
    Blob decrypted=Crypto.decryptWithManagedIV('AES128', key, decodedEncryptedData);
    String toStringData=decrypted.toString();
    system.debug(toStringData);
```

## 原因の推測

generateAesKeyで生成されるBlob内にtoStringで変換するutf-8の形式に対応していない文字列が含まれているから変換できないのかなと推測しておりますが、
このエラーの原因がわかる方いらっしゃいましたらコメントなどで教えていただけると嬉しいです。