<template>
  <p>请输入邮箱号：&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195</p>
  <p>邮箱：&#8195<input type="txet" v-model="email"/></p>
  <p>
    请点击发送验证码：&#8195
    <button @click="sentvcode()">发送验证码</button>
  </p>
  <p>验证码：<input type="txet" v-model="verification_code"/></p>
  <p>请输入用户名：&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195</p>
  <p>用户名：<input type="txet" v-model="verification_code"/></p>
  <p>请输入密码：&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195</p>
  <p>密码：&#8195<input type="password" v-model="password1"></p>
  <p>请重复输入密码：&#8195&#8195&#8195&#8195&#8195&#8195&#8195</p>
  <p>密码：&#8195<input type="password" v-model="password2"></p>
  <p>
    <button @click="relogin()">&#8195返回&#8195</button>
    &#8195&#8195&#8195&#8195&#8195&#8195
    <button @click="register()">&#8195注册&#8195</button>   
  </p>
  <p>{{count}}</p>
  <p>注：密码长度为6-10位，必须包含大小写字母和数字</p>
</template>

<script>
import axios from 'axios'
export default (await import('vue')).defineComponent({
  data() {
    return {
      email:null,
      verification_code:null,
      username:null,
      password1:null,
      password2:null,
    }
  },
  mounted: function(){
    this.init();
  },
  methods: {
    init(){
      this.account=null;
      this.email=null;
      this.verification_code=null;
      this.password1=null;
      this.password2=null
    },
    sentvcode() {
      if(this.email==null) {
        alert("emial should be not null");
        return;
      }
      var returnData = {
        email:this.email,
      }
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://120.78.196.67:8000/signinpre",JSON.stringify(returnData))
        .then((res)=>{
          if(res.data.success == true) {//发送验证码成功
            alert("发送成功");
          }
          else {
            alert("发送失败");
          }
        })
    },
    register() {
      alert("注册");
      var returnData = {
        username:this.username,
        password1:this.password1,
        password2:this.password2,
        email:this.email,
        verifycode:this.verification_code
      }
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://120.78.196.67:8000/signin",JSON.stringify(returnData))
        .then((res)=>{
          alert(res.data.info)
          if(res.data.success==true){//注册成功，并登录
            $store.state.account=this.email;
            $store.state.password=this.password1;
            $store.state.iflogin=true;
            this.$router.push("/select_difficulty");
          }
        })
    },
    relogin() {
      this.$router.push("/");
    }
  }
})
</script>