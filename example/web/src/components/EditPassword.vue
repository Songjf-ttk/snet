<template>
  <h3>请输入旧密码&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195</h3>
  <p>旧密码：<input type="password" v-model="old_password"></p>
  <h3>请输入新密码&#8195&#8195&#8195&#8195&#8195&#8195&#8195&#8195</h3>
  <p>新密码：<input type="password" v-model="new_password1"></p>
  <h3>请重复输入新密码&#8195&#8195&#8195&#8195&#8195&#8195</h3>
  <p>新密码：<input type="password" v-model="new_password2"></p>
  <p>
    请点击提交：&#8195&#8195&#8195&#8195&#8195
    <button @click="submit()">&#8195提交&#8195</button>
  </p>
  <button @click="reselect()">&#8195返回&#8195</button>
</template>

<script>
import axios from 'axios'
import { initCustomFormatter } from 'vue';
export default (await import('vue')).defineComponent({
  data() {
    return {
      old_password:null,
      new_password1:null,
      new_password2:null
    }
  },
  mounted: function(){
    this.init();
  },
  methods: {
    init(){
      this.old_password=null;
      this.new_password1=null;
      this.new_password2=null;
    },
    submit() {
      var returnData = {
        oldpassword:this.old_password,
        newpassword1:this.new_password1,
        newpassword2:this.new_password2,
        account:this.$store.state.account
      };
      alert(JSON.stringify(returnData));
      axios.defaults.headers.post["Content-Type"] = "application/json";
      axios
        .post("http://120.78.196.67:8000/reset-password",JSON.stringify(returnData))
        .then ( (res) =>{
          alert(res.data.info);
          if(res.data.success == true){//修改成功
            this.$router.push("/select_difficulty");
          }
        })
    },
    reselect() {
      this.$router.push("/select_difficulty");
    }
  },
  
})

</script>