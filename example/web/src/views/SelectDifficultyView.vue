<template>
  用户名：{{ this.$store.state.username }}
  <p>
    <button @click="edit_password()">修改密码</button> |
    <button @click="relogin()">退出登录</button>
  </p>
  <SelectDifficulty/>
</template>

<script>
import SelectDifficulty from '@/components/SelectDifficulty.vue';
import axios from 'axios'
import { initCustomFormatter } from 'vue';
export default {
  name: 'SelectDiffuicultyView',
  components: {
    SelectDifficulty
  },
  mounted: function(){
    this.init()
  },
  methods: {
    init() {
      if(this.$store.state.islogin==false) {
        alert("您还没有登录，点击确定返回登录界面");
        this.$router.push('/')
      }
    },
    relogin() {
      /*    无用
      var returnData = {};
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://localhost:8000/logout",JSON.stringify(""))
        .then((res)=>{
          if(res.data.success == true){发送题目信息,获取返回
            this.$router.push("/");
          }
      })*/
      this.$router.push("/");
    },
    edit_password() {
      this.$router.push("/edit_password");
    }
  }
}
</script>