import { Controller, Get, Post, Body, Patch, Param, Delete } from '@nestjs/common';
import { ChannelService } from './channel.service';
import { PostChannelDto } from './dto/post-channel.dto';
import { UpdateChannelDto } from './dto/update-channel.dto';

@Controller('channel')
export class ChannelController {
  constructor(private readonly channelService: ChannelService) {}

  @Post()
  createChannel(@Body() postChannelDto: PostChannelDto) {
    console.log("channel_post");
    console.log(postChannelDto);
    return this.channelService.createChannel(postChannelDto);
  }

  @Get()
  async getAllChannelList() {
    console.log("channel_get");
    return {channelList : await this.channelService.getAllChannelList()};
  }

  @Get(':id')
  async getOneChannel(@Param('id') id: number) {
    console.log(`getOneChannel ${id}` );
    return await this.channelService.findOne(id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateChannelDto: UpdateChannelDto) {
    return this.channelService.update(+id, updateChannelDto);
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.channelService.remove(+id);
  }
}
