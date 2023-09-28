<template>
    <div class="get_mark">
      <h1>用户：{{ this.$store.state.username }}</h1>
      <h1 class="Get">最终得分：<br><br>{{ this.mark }}</h1>
    </div>
    <button @click="reselect()">完成</button>

  </template>
  
<script>
// @ is an alias to /src
import axios from 'axios'
import { initCustomFormatter } from 'vue';
  
export default {
  name: 'GrtMarkView',
  data() {
      return {
          mark:0.0,
      }
  },
  mounted:function(){
    this.init();
  },
  methods: {
    init(){
      if(this.$store.state.islogin==false) {
        alert("您还没有登录，点击确定返回登录界面");
        this.$router.push(' /')
        return;
      }
      var returnData = {
        account:this.$store.state.account
      }
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://120.78.196.67:8000/get-score",JSON.stringify(returnData))
        .then((res)=>{
          if(res.data.success == false){发送题目信息,获取返回
            alert("获取分数失败");
          }else {//获取分数
            this.mark=res.data.score;
          }
      })
    },
    reselect() {
      this.$router.push('/select_difficulty')
    }
  }
}
</script>