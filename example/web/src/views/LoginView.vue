<template>
  <div class="login">
    <h1 class="">小初高数学题目自动生成系统</h1>
    <Login/>
  </div>
</template>

<script>
// @ is an alias to /src


import Login from '@/components/Login.vue'

export default {
  name: 'LoginView',
  components: {
    Login
  },
  mounted: function() {
    this.init()
  },
  methods: {
    init() {
      this.$store.state.account=null;
      this.$store.state.username=null;
      this.$store.state.islogin=false;
      this.$store.state.grade=null;
      this.$store.state.num=10;
    }
  }
}
</script>