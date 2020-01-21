# 概要

AtCoder上でのAC数を1日1回ログインしたツイッターアカウントでツイートしてくれるdevotterというアプリケーションを作成したよというお話

## リンク

- <https://devotter.app/>

## スライド

- <https://www.slideshare.net/KaoruIshizawa/devotter>

## GitHub

- <https://github.com/10kaoru12/devotter_backend>
- <https://github.com/10kaoru12/devotter_frontend>

## ソースコード（フロントエンド）

```vue
<template>
  <v-container pa-12 fill-height>
    <v-layout align-center text-center wrap>
      <v-flex xs12>
        <v-alert v-model="alert" type="error" dismissible>{{errorMessage}}</v-alert>
        <v-alert v-model="success" type="success" dismissible>SUCCESS!</v-alert>
        <v-img :src="require('../assets/thai monk.svg')" class="my-3" contain height="200"></v-img>
        <h1>「Devotter」</h1>
        <h2>
          その精進
          <br />ツイートしませんか
        </h2>
        <br />
        <h5>このアプリケーションは、1日1回AtCoderでのAC数をTwitterにツイートしてくれるアプリケーションです。</h5>
        <br />
        <v-form>
          <v-text-field
            @change="changeField"
            type="text"
            v-model="atcoderId"
            v-if="login"
            label="AtCoderID"
            color="#00acee"
            required
          ></v-text-field>
        </v-form>
        <v-btn
          @click="signin"
          v-bind:disabled="isnull"
          v-show="login"
          color="#00acee"
          rounded
        >Sign In To Twitter</v-btn>
        <v-btn @click="logout" v-show="!login" color="#00acee" rounded>Log Out from Twitter</v-btn>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
import firebase from "firebase";
import axios from "axios";

export default {
  name: "guestUserScreen",
  methods: {
    logout: function() {
      firebase
        .auth()
        .signOut()
        .then(()=>{
          this.success=true;
          this.login=true;
        })
        .catch(()=>{
          this.alert=true;
          this.errorMessage="サインアウトに失敗しました。"
        });
    },
    signin: function() {
      var db = firebase.firestore();
      var document = this.atcoderId;
      axios
        .get(this.userApi + this.atcoderId)
        .then(response => {
          this.userInfo = response;
          const provider = new firebase.auth.TwitterAuthProvider();
          this.success = true;
          firebase
            .auth()
            .signInWithPopup(provider)
            .then(function(result) {
              let token = result.credential.accessToken;
              let secret = result.credential.secret;
              db.collection("users")
                .doc(document)
                .set({
                  accessToken: token,
                  accessTokenSecret: secret
                });
            })
            .catch(function() {
              this.alert = true;
              this.errorMessage = "ERROR!";
            });
        })
        .catch(() => {
          this.alert = true;
          this.errorMessage = "無効なAtCoderID名です。";
        });
    },
    changeField: function() {
      this.atcoderId ? (this.isnull = false) : (this.isnull = true);
    }
  },
  created: function() {
    firebase.auth().onAuthStateChanged(user => {
      if (user) {
        this.login = false;
      }
    });
  },
  data: function() {
    return {
      atcoderId: "",
      isnull: true,
      userInfo: "",
      userApi: "https://kenkoooo.com/atcoder/atcoder-api/v2/user_info?user=",
      alert: false,
      errorMessage: "",
      success: false,
      login: true
    };
  }
};
</script>
```

## ソースコード（バックエンド）

```js
//import
const functions = require('firebase-functions');
const admin = require('firebase-admin');
const serviceAccount = require('./atcontributter-firebase-adminsdk-5p86i-6e55085ef8.json');
const axios = require('axios');
const twitter = require('twitter');
const cors = require('cors')({ origin: true });
const decycle = require('json-decycle').decycle;
const retrocycle = require('json-decycle').retrocycle;

//initialize
const adminConfig = JSON.parse(process.env.FIREBASE_CONFIG);
adminConfig.credential = admin.credential.cert(serviceAccount);
admin.initializeApp(adminConfig);

//create instance
const firestore = admin.firestore();
const bucket = admin.storage().bucket();

//global
let consumerKey;
let consumerKeySecret;
let accessToken;
let accessTokenSecret;
let receiveAc;
let receiveNewAcString;
let receiveNewAc;
let senderAc;
let uploadPath;
let problemCount;
let newProblemCount;

//main
exports.devotterCronJob = functions.region('asia-northeast1').https.onRequest(async (request, response) => {
    cors(request, response, () => {
        response.set('Access-Control-Allow-Origin', 'http://localhost:5000');
        response.set('Access-Control-Allow-Methods', 'GET, HEAD, OPTIONS, POST');
        response.set('Access-Control-Allow-Headers', 'Content-Type');
    });
    try {
        //firebase storageから昨日のAtCoderAC情報が入ったjsonを取得する
        const receiveJson = await bucket.file('ac.json').download();
        receiveAc = JSON.parse(receiveJson);

        //kenkooooさんのAtCoderAPIを使って本日のAtCoderAC情報をaxiosで取得
        const receiveNewJson = await axios.get('https://kenkoooo.com/atcoder/resources/ac.json', { headers: { 'accept-encoding': 'gzip' } });
        receiveNewAcString = JSON.stringify(receiveNewJson, decycle());
        receiveNewAc = JSON.parse(receiveNewAcString, retrocycle()).data;

        //firestoreからtwitter apiのconsumerKeyとconsumerKeySecretを取得
        const getConsumerKeyQuerySnapShot = await firestore.collection('api').doc('keys').get();
        consumerKey = getConsumerKeyQuerySnapShot.data().consumerKey;
        consumerKeySecret = getConsumerKeyQuerySnapShot.data().consumerKeySecret;

        //firestoreからツイートに必要なユーザー情報を取得
        const getUserDataQuerySnapShot = await firestore.collection('users').get();
        getUserDataQuerySnapShot.forEach(async document => {
            try {
                //取得したUserQuerySnapShotからaccessTokenとaccessTokenSecretを取得
                const getAcceseTokenQuerySnapShot = await firestore.collection('users').doc(document.id).get();
                accessToken = getAcceseTokenQuerySnapShot.data().accessToken;
                accessTokenSecret = getAcceseTokenQuerySnapShot.data().accessTokenSecret;

                //昨日のjsonデータ中のfirestoreに登録しているユーザーのAC数を抽出
                for (const element in receiveAc) {
                    if (receiveAc[element].user_id === document.id) {
                        problemCount = receiveAc[element].problem_count;
                        break;
                    }
                }

                //今日のjsonデータ中のfirestoreに登録しているユーザーのAC数を抽出
                for (const element in receiveNewAc) {
                    if (receiveNewAc[element].user_id === document.id) {
                        newProblemCount = receiveNewAc[element].problem_count;
                        break;
                    }
                }

                //twitterクライアントにkeyを登録
                const client = new twitter({
                    consumer_key: consumerKey,
                    consumer_secret: consumerKeySecret,
                    access_token_key: accessToken,
                    access_token_secret: accessTokenSecret
                });

                //twitter apiを使ってツイート
                let tweetMessage = '今日の' + document.id + 'さんのAC数は' + (newProblemCount - problemCount) + 'でした。\n#devotter'
                client.post('statuses/update', {
                    status: tweetMessage
                }, (error) => {
                    if (!error) {
                        response.status(200).send('success!');
                    }
                    else {
                        response.status(500).send(error);
                    }
                });

                //今日取得したAC数をfirebase storageにアップロード
                senderAc = JSON.stringify(receiveNewAc);
                uploadPath = 'ac.json';
                bucket.file(uploadPath).save(senderAc);
            }
            catch (error) {
                response.status(500).send(error);
            }
        });
    }
    catch (error) {
        response.status(500).send(error);
    }
});
```
