<template>
  <h2>{{ now_num+':'+problem }}</h2>
  <p v-for="value,key,index in selection">
    <input type="radio" v-model="answer" :value="key">{{ key }}：{{ value }}
  </p>
  <button @click="get_mark()">&nbsp交卷&nbsp</button>
  <div v-if="now_num<this.$store.state.num"  style="display:inline">
    &#8195&#8195&#8195
    <button @click= "submit_answer();get_problem()">下一题</button>
  </div><br><br>
  注：请不要刷新页面，否则需要重新做题
  <br><br>
  {{ now_num }}/{{ this.$store.state.num }}<br>
</template>

<script>
import axios from 'axios'
import { initCustomFormatter } from 'vue';
export default (await import('vue')).defineComponent({
  data() {
    return {
      now_num:0,
      problem:null,
      selection:{
        A:null,
        B:null,
        C:null,
        D:null
      },
      answer:null
    }
  },
  mounted: function(){
    this.init();
    this.get_problem();
  },
  methods: {
    init(){
      if(this.$store.state.islogin==false) {
        alert("您还没有登录，点击确定返回登录界面");
        //this.$router.push('/')
      }else if(this.$store.grade == ""){
        alert("你还没有选择难度，点击确认返回题目难度界面");
        this.$router.push("/selectdifficulty");
      }
      this.now_num=0;
      this.problem=null;
      this.selection.A=null;
      this.selection.B=null;
      this.selection.C=null;
      this.selection.D=null;
      this.answer=null;
    },
    get_problem() {
      this.now_num +=1;
      var returnData = {
        questionId:this.now_num,
        account:this.$store.state.account
      }
      alert(JSON.stringify(returnData));
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://120.78.196.67:8000/get-question/"+this.now_num,JSON.stringify(returnData))
        .then((res)=>{
          this.problem=res.data.question;
          this.selection.A=res.date.optionA;
          this.selection.B=res.data.optionB;
          this.selection.C=res.date.optionC;
          this.selection.D=res.data.optionD;
        })
    },
    submit_answer() {
      if(this.answer==null){
        alert("请选择答案");
        return
      }
      var returnData = {
        n_problem:this.now_num,
        answer:this.answer,
        account:this.account
      }
      alert(JSON.stringify(returnData));
      alert(JSON.stringify(returnData));
      axios.defaults.headers.post["Content-type"]="application/json";
      axios
        .post("http://120.78.196.67:8000/upload-abswer",JSON.stringify(returnData))
        .then((res)=>{
        })
      this.answer = null;
    },
    get_mark() {
      this.$store.state.grade = "";
      this.$router.push("/get_mark")
    }
  },
})

</script>