<template>
  <div class="Problem">
    <h1 class="">数学题目</h1>
    用户名：{{ this.$store.state.username }}
    <br><br>
    <Problem/>
  </div>
</template>
<script>
  // @ is an alias to /src
  
import Problem from '@/components/Problem.vue';

export default {
  name: 'ProblemView',
  components: {
  Problem
  },
  mounted: function(){
    this.init()
  },
  methods: {
    init(){
      if(this.$store.state.islogin==false) {
        alert("您还没有登录，点击确定返回登录界面");
        this.$router.push('/')
      }
    }
  }
}
</script>