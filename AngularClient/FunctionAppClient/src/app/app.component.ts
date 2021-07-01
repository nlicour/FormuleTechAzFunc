import { Component } from '@angular/core';
import { LedControllerService } from './led-controller.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})

export class AppComponent {
  color: any = {
    r: 0, g: 0, b: 0
  };
  title = 'FunctionAppClient';

  constructor(private ledControllerService: LedControllerService) {

  }

  async switchOnAsync() {
    let message = await this.ledControllerService.switchLedPowerState(true);
    console.log(message)
  }

  async switchOffAsync() {
    let message = await this.ledControllerService.switchLedPowerState(false);
    console.log(message)
  }

  async setLedRgbAsync() {
    let message = await this.ledControllerService.setLedRgb(this.color.r, this.color.g, this.color.b);
    console.log(message)
  }

}
