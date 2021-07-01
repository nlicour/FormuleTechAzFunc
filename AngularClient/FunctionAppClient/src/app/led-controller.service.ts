import { Injectable } from '@angular/core';
import { environment } from 'src/environments/environment';
import { HttpHeaders, HttpClient, HttpParams } from '@angular/common/http';

const headers = new HttpHeaders().set('Accept', 'text/plain');
@Injectable({
  providedIn: 'root'
})
export class LedControllerService {

  api = environment.baseApiUrl;

  setLedRgbFunctionKey = environment.setLedRegbKey;
  setLedStateFunctionKey = environment.setLedStateFunctionKey;


  constructor(private http: HttpClient) { }

  switchLedPowerState(state: boolean) {
    const url = `${this.api}/SetLedState`;
    const params = { state: state ? 1 : 0, code: this.setLedStateFunctionKey };
    return this.http.get<string>(url, {params, headers}).toPromise();
  }

  setLedRgb(r: number, g: number, b: number) {
    const url = `${this.api}/SetLedRgb`;
    const params = { 
      red: r,
      green: g,
      blue: b,
      code: this.setLedRgbFunctionKey
     };
    return this.http.get<string>(url, {params, headers}).toPromise();
  }
}
