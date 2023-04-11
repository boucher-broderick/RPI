import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  password = '';
  length = 0;
  includeLetters = false;
  includeNumbers = false;
  includeSymbols = false;


  onChangeLength(value: string){
    const parsedValue = parseInt(value);
    if(!isNaN(parsedValue)){
      this.length = parsedValue;
    }
    else{
      console.log(' invalid length')
    }
  }

  OnChangeUseLetters(){
    this.includeLetters = !(this.includeLetters);
  }

  OnChangeUseNumbers(){
    this.includeNumbers = !(this.includeNumbers);
  }
  OnChangesUseSymbols(){
    this.includeSymbols = !(this.includeSymbols);
  }

  onButtonClick(){
    const numbers = '1234567890';
    const letters = 'qwertyuioplkjhgfdsazxcvbnm';
    const symbols = '!@#$%^&*()';

    let validChars = '';
    if(this.includeLetters){
      validChars+=letters;
    }
    if(this.includeNumbers){
      validChars+=numbers;
    }
    if(this.includeSymbols){
      validChars+=symbols;
    }
    let generatedPassword = '';
      for(let i =0; i<this.length; i++){
        const index = Math.floor(Math.random() * validChars.length);
        generatedPassword+=validChars[index];
      }
      this.password = generatedPassword;
  }
}
