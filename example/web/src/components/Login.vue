<template>
  <p>账号：<input type="text" v-model="account"/></p>
  <p>密码：<input  type="password" v-model="password"/></p>
  <p>
      <button @click="login()">登录</button>
      &emsp;&emsp;
      <button @click="register()">注册</button>
  </p>
</template>

<script>
import axios from 'axios'
export default (await import('vue')).defineComponent({
  data() {
    return {
      account: null,
      password: null
    };
  },
  mounted:function(){
    this.init();
  },
  methods: {
    init(){
      this.account=null;
      this.password=null;
    },
    login() {
      var returnData = {
        account: this.account,
        password: this.password
      };
      //alert("进行登录");
      //alert(JSON.stringify(returnData));
      axios.defaults.headers.post["Content-Type"] = "application/json";
      axios
        .post("http://120.78.196.67:8000/login",JSON.stringify(returnData))
        .then ( (res) =>{
          //alert(res.data.str);
          if(res.data.success == false){
            alert(res.data.info);
          }
          else{
            this.$store.state.username=res.data.username;
            this.$store.state.account = this.account;
            this.$store.state.islogin = true;
            this.$router.push("/select_difficulty");
          }
        })
    },
    register() {
      this.$router.push("/register");
    }
  },
});
</script>