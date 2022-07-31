import { Controller, Get, Post, Body, Patch, Param, Delete } from '@nestjs/common';
import { ChannelService } from './channel.service';
import { PostChannelDto } from './dto/post-channel.dto';
import { UpdateChannelDto } from './dto/update-channel.dto';

@Controller('channel')
export class ChannelController {
  constructor(private readonly channelService: ChannelService) { }

  @Post()
  createChannel(@Body() postChannelDto: PostChannelDto) {
    // console.log("channel_post");
    return this.channelService.createChannel(postChannelDto);
  }

  @Get()
  async getAllChannelList() {
    // console.log("channel_get");
    return { channelList: await this.channelService.getAllChannelList() };
  }

  @Get(':channelid')
  getOneChannel(@Param('channelid') channelid: number) {
    console.log(`getOneChannel ${channelid}`);
    return this.channelService.getOneChannel(channelid);
  }

  @Patch(':channelid/password')
  updatePassword(@Param('channelid') channelid: number, @Body() updateChannelDto: UpdateChannelDto) {
    console.log("updatePassword");
    return this.channelService.updatePassword(channelid, updateChannelDto);
  }

  @Patch(':channelid/entry')
  updateCurNumUser(@Param('channelid') channelid: number) {
    console.log("updateCurNumUser");
    return this.channelService.updateCurNumUser(channelid);
  }

  @Delete(':channelid')
  remove(@Param('channelid') channelid: number) {
    return this.channelService.remove(+channelid);
  }
}
