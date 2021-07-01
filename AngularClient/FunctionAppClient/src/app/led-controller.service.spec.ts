import { TestBed } from '@angular/core/testing';

import { LedControllerService } from './led-controller.service';

describe('LedControllerService', () => {
  let service: LedControllerService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(LedControllerService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
