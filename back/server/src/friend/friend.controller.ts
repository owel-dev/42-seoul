import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  Query,
  HttpCode,
  UseGuards,
} from '@nestjs/common';
import { FriendService } from './friend.service';
import { CreateFriendDto } from './dto/create-friend.dto';
import { UpdateFriendDto } from './dto/update-friend.dto';
import { DeleteFriendDto } from './dto/delete-friend.dto';
import { AuthGuard } from 'src/auth/auth.guard';
import { Token } from 'src/auth/auth.decorator';

@Controller('friend')
export class FriendController {
  constructor(private readonly friendService: FriendService) {}

  @Post()
  @UseGuards(AuthGuard)
  create(@Token() token: string, @Body() createFriendDto: CreateFriendDto) {
    return this.friendService.create(token, createFriendDto);
  }

  @Get(':nickname')
  @UseGuards(AuthGuard)
  findOne(@Param('nickname') nickName: string) {
    return this.friendService.getFriendListOne(nickName);
  }

  @Delete()
  @UseGuards(AuthGuard)
  @HttpCode(204)
  deleteFriend(@Token() token: string, @Query('user') nickName) {
    return this.friendService.deletefriend(token, nickName);
  }
}
