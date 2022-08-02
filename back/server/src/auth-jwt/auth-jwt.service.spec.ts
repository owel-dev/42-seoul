import { Test, TestingModule } from '@nestjs/testing';
import { AuthJwtService } from './auth-jwt.service';

describe('AuthJwtService', () => {
  let service: AuthJwtService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [AuthJwtService],
    }).compile();

    service = module.get<AuthJwtService>(AuthJwtService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
